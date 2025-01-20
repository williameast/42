/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/20 12:21:13 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_crd	populate_coordinate(int x, int y, char *z)
{
	t_crd	out;

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

static int	get_coordinates_array(t_crd *points, char **split, int y, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		points[i] = populate_coordinate(i, y, split[i]);
		if (points[i].visible == -1)
			return (0);
		i++;
	}
	return (1);
}

t_crd	*parse_row_to_coordinates(char *row, int y, int *count)
{
	t_crd	*coordinates;
	char	**split;

	if (!row || !count)
		return (NULL);
	split = ft_split(row, ' ');
	if (!split)
		return (NULL);
	*count = 0;
	while (split[*count])
		(*count)++;
	coordinates = malloc(sizeof(t_crd) * (*count));
	if (!coordinates || *count == 0)
	{
		free_char_array(split);
		return (NULL);
	}
	if (!get_coordinates_array(coordinates, split, y, *count))
	{
		free(coordinates);
		free_char_array(split);
		return (NULL);
	}
	free_char_array(split);
	return (coordinates);
}

int	append_row_to_map(t_map *map, t_crd *row_coords, int row_length)
{
	t_crd	*new_points;
	int		i;

	i = 0;
	new_points = realloc(map->points, sizeof(t_crd)
			* (map->points_len + row_length));
	if (!new_points)
		return (0);
	map->points = new_points;
	while (i < row_length)
	{
		map->points[map->points_len + i] = row_coords[i];
		i++;
	}
	if (row_length > map->cols)
		map->cols = row_length;
	map->rows++;
	map->points_len += row_length;
	return (1);
}
