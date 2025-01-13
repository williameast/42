/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/12 18:29:41 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_crd populate_coordinate(int x, int y, char *z)
{
    t_crd out;

    out.x = x;
    out.y = y;
    out.grid_x = x;
    out.grid_y = y;
    if (z[0] != '\0')
    {
        out.z = ft_atoi(z);
        out.grid_z = out.z;
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

// Function to read the full map as a single string
char *read_full_map_as_str(char *file)
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

// Function to split rows into a coordinate array
// TODO: make sure that empty rows are handled!!!
static t_crd *parse_row_to_coordinates(char *row, int y, int *count)
{
    char **split;
    t_crd *coordinates;
    int i;

    if (!row || !count)
        return (NULL);
    split = ft_split(row, ' ');
    if (!split)
        return (NULL);
    *count = 0;
    while (split[*count])
        (*count)++;
    coordinates = malloc(sizeof(t_crd) * (*count));
    if (!coordinates || *count == 0) // return NULL if line is empty!
    {
        free_char_array(split);
        return NULL;
    }
    for (i = 0; i < *count; i++)
    {
        coordinates[i] = populate_coordinate(i, y, split[i]);
        if (coordinates[i].visible == -1)
        {
            free(coordinates);
            free_char_array(split);
            return (NULL);
        }
    }
    free_char_array(split);
    return (coordinates);
}

t_map *initialize_map()
{
	ft_printf("INFO: initializing map...\n");
    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return NULL;
    map->points = NULL;
    map->points_len = 0;
    map->rows = 0;
    map->cols = 0;
    map->x_max = INT_MIN;
    map->x_min = INT_MAX;
    map->y_max = INT_MIN;
    map->y_min = INT_MAX;
    map->z_max = INT_MIN;
    map->z_min = INT_MAX;
	ft_printf("INFO: initialized map.\n");
    return map;
}

static int append_row_to_map(t_map *map, t_crd *row_coords, int row_length)
{
    t_crd *new_points;

    new_points = realloc(map->points, sizeof(t_crd) * (map->points_len + row_length));
    if (!new_points)
        return 0;
    map->points = new_points;
    for (int i = 0; i < row_length; i++)
        map->points[map->points_len + i] = row_coords[i];
    if (row_length > map->cols)
        map->cols = row_length;
    map->rows++;
    map->points_len += row_length;
    return 1;
}

// Function to read and split the map file into rows
static char **read_and_split_map(char *filename)
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

// Function to process a single row and append it to the map
// TODO you could use this to send a -1 signal indicating an empty line.
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

t_map *parse_map(char *filename)
{
    char **row_split;

	row_split = read_and_split_map(filename);
    if (!row_split)
        return NULL;
    t_map *map = initialize_map();
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
