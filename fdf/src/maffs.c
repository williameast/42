/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maffs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:34:41 by William           #+#    #+#             */
/*   Updated: 2025/01/18 13:57:58 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ternary(int a, int b, int c)
{
	if (a)
		return (b);
	else
		return (c);
}

int	is_pixel_out_of_bounds(t_crd p)
{
	return (p.x < 0 || p.y < 0
		|| p.x >= WIN_WIDTH || p.y >= WIN_HEIGHT);
}

void	get_coordinate_limits(t_map *map)
{
	int		i;
	t_crd	coordinate;

	i = 0;
	while (i < map->points_len)
	{
		coordinate = map->points[i];
		if (coordinate.x < map->x_min)
			map->x_min = coordinate.x;
		if (coordinate.x > map->x_max)
			map->x_max = coordinate.x;
		if (coordinate.y < map->y_min)
			map->y_min = coordinate.y;
		if (coordinate.y > map->y_max)
			map->y_max = coordinate.y;
		if (coordinate.z < map->z_min)
			map->z_min = coordinate.z;
		if (coordinate.z > map->z_max)
			map->z_max = coordinate.z;
		i++;
	}
}

float	get_z_scale_factor(t_map *map)
{
	float	xyrange;
	float	z_scale;
	float	x_range;
	float	y_range;
	float	z_range;

	x_range = map->x_max - map->x_min;
	y_range = map->y_max - map->y_min;
	z_range = map->z_max - map->z_min;
	if (x_range > y_range)
		xyrange = x_range;
	else
		xyrange = y_range;
	z_scale = z_range / xyrange;
	return (z_scale * Z_SCALE);
}
