/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:50:32 by William           #+#    #+#             */
/*   Updated: 2025/01/18 14:09:36 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int process_row(t_map *map, char *row, int row_index)
{
    int row_count = 0;
    t_crd *row_coords = parse_row_to_coordinates(row, row_index, &row_count);
    if (!row_coords)
        return 0; // Indicates failure
    if (!append_row_to_map(map, row_coords, row_count))
    {
        free(row_coords);
        return 0; // Indicates failure
    }
    free(row_coords);
    return 1; // Indicates success
}

// Function to read the full map as a single string
static char *read_full_map_as_str(char *file)
{
    int fd;
    char *full_line;
    char *next_line;
    char *temp;

    full_line = ft_strdup("");
    if ((fd = open(file, O_RDONLY)) < 0 || !check_extension(file, ".fdf"))
    {
        ft_printf("ERROR: <%s> is not valid or could not be found.\n", file);
        free(full_line);
        return (NULL);
    }
    while ((next_line = get_next_line(fd)) != NULL)
    {
        temp = ft_strjoin(full_line, next_line);
        free(full_line);
        full_line = temp;
        free(next_line);
    }
    close(fd);
    return (full_line);
}

// Function to read and split the map file into rows
char **read_and_split_map(char *filename)
{
    char *map_str = read_full_map_as_str(filename);

    if (DEBUG)
        ft_printf("INFO: map string: \n%s\n", map_str);
    if (!map_str)
        return NULL;
    char **row_split = ft_split(map_str, '\n');
    free(map_str);
    if (!row_split)
        ft_printf("ERROR: Failed to split map string into rows.\n");
    return row_split;
}

t_map *parse_map(char *filename)
{
    char **row_split;
	t_map	*map;

	row_split = read_and_split_map(filename);
    if (!row_split)
		return NULL;
	map = init_map();
    if (!map)
    {
        free_char_array(row_split);
        return NULL;
    }
    for (int i = 0; row_split[i] != NULL; i++)
    {
        if (!process_row(map, row_split[i], i))
        {
            free_map(map);
            free_char_array(row_split);
            return NULL;
        }
    }
    free_char_array(row_split);
    get_coordinate_limits(map);
    return map;
}
