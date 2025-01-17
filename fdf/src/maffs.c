/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maffs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:34:41 by William           #+#    #+#             */
/*   Updated: 2025/01/17 16:01:39 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


int	derivative_of(int a, int b)
{
    return(abs(a - b));
}

int	pos_or_neg(int a, int b)
{
    if (a < b)
        return (1);
    return (-1);
}

int ternary(int a, int b, int c)
{
    if (a)
        return (b);
    else
        return (c);
}

int	is_pixel_out_of_bounds(t_crd p)
{
    return (p.x < 0 || p.y < 0 ||
        p.x >= WIN_WIDTH || p.y >= WIN_HEIGHT);
}

void	get_coordinate_limits(t_map *map)
{
    int	i;
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

int get_colour_gradient(float z, int z_min, int z_max)
{
    float proportion;

    // Avoid division by zero
    if (z_max == z_min)
        return 0x0000FF; // Default to start color if no range

    // Calculate the proportion of z within the range
    proportion = (z - z_min) / (float)(z_max - z_min);

    // Clamp proportion to [0, 1]
    if (proportion < 0.0f) proportion = 0.0f;
    if (proportion > 1.0f) proportion = 1.0f;


    // Interpolate between start (blue) and end (red) colors
    int start_color = 0x0000FF;  // Blue
    int end_color = 0xFF0000;    // Red

    int start_r = (start_color >> 16) & 0xFF;
    int start_g = (start_color >> 8) & 0xFF;
    int start_b = start_color & 0xFF;

    int end_r = (end_color >> 16) & 0xFF;
    int end_g = (end_color >> 8) & 0xFF;
    int end_b = end_color & 0xFF;

    int r = (int)(start_r + proportion * (end_r - start_r));
    int g = (int)(start_g + proportion * (end_g - start_g));
    int b = (int)(start_b + proportion * (end_b - start_b));

    return (r << 16) | (g << 8) | b;
}
