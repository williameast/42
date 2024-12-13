/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2024/12/13 16:30:20 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// creates a single coordinate.
// visible = 1 means point is to be plotted.
// visible = 0 means point should be skipped. we keep the point
// to make managament of the grid easier
// visible = -1 indicates that the detected value is invalid (i.e. not a valid integer)
// this is used to "fail" the map-generation process.
t_crd populate_coordinate(int x, int y, char *z)
{
	t_crd out;

	out.x = x;
	out.y = y;
	if (z[0] != '\0')
	{
		out.z = ft_atoi(z);
		if (out.z == 0 && z[0] != '0')
		{
			out.visible = -1;
			ft_printf("ERROR: Invalid input of <%s> detected.\n", z);
		}
		else
			out.visible = 1;
	}
	else
	{
		out.z = 0;
		out.visible = 0;
	}
	return (out);
}
// creates a string with the full length of the map.
char	*read_full_map_as_str(char	*file)
{
	int	fd;
	char	*full_line;
	char	*next_line;
	char	*temp;

	full_line = ft_strdup("");
	if ((fd = open(file, O_RDONLY)) < 0 || !check_extension(file, ".fdf"))
	{
		ft_printf("ERROR: <%s> is not valid or could not be found.\n", file);
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
	free(temp);
	return (full_line);
}

t_crd	*parse_row_to_coordinates(char *row, int y, int *count)
{
	char **split;
	t_crd *coordinates;
	int	i;

	if (!row || !count)
		return (NULL);
	split = ft_split(row, ' ');
	if (!split)
		return (NULL);
	*count = 0;
	while (split[*count])
		(*count)++;
	coordinates = malloc(sizeof(t_crd) * (*count));
	if (!coordinates)
		return NULL;
	i = 0;
	while (i < *count)
	{
		coordinates[i] = populate_coordinate(i, y, split[i]);
		if (coordinates[i].visible == -1)
		{
			free(coordinates);
			free_char_array(split);
			return (NULL);
		}
		i++;
	}
	free_char_array(split);
	return (coordinates);
}

char **split_rows(const char *map_str)
{
    char **rows;

	rows = ft_split(map_str, '\n');
    if (!rows)
        ft_printf("ERROR: Row split allocation failed.\n");
    return (rows);
}

// Function to append row coordinates to the map array, reallocating memory as needed
int append_row_to_map(t_crd **map, int *total_count, t_crd *row_coords, int row_count)
{
    t_crd	*new_map;
	new_map = realloc(*map, sizeof(t_crd) * (*total_count + row_count));
    if (!new_map)
        return 0; // Allocation failure
    *map = new_map;
    for (int j = 0; j < row_count; j++)
        (*map)[*total_count + j] = row_coords[j];
    *total_count += row_count;
    return 1; // Success
}

// Main function to parse the map string into a t_crd array
t_crd *parse_map(const char *map_str, int *total_coordinates)
{
    char **row_split = split_rows(map_str);
    if (!row_split)
        return NULL;
    t_crd *map = NULL;
    int total_count = 0;
    for (int i = 0; row_split[i] != NULL; i++)
    {
        int row_count = 0;
        t_crd *row_coords = parse_row_to_coordinates(row_split[i], i, &row_count);
        if (!row_coords)
        {
            free(map);
            free_char_array(row_split);
            return NULL;
        }
        if (!append_row_to_map(&map, &total_count, row_coords, row_count))
        {
            free(row_coords);
            free(map);
            free_char_array(row_split);
            return NULL;
        }
        free(row_coords); // Free row_coords after copying its contents
    }
    free_char_array(row_split);
    *total_coordinates = total_count;
    return map;
}
