/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:19:40 by William           #+#    #+#             */
/*   Updated: 2025/01/12 14:54:45 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	translate(t_ctrl *session, int dx, int dy)
{
    session->offset.x_offset += dx;
    session->offset.y_offset += dy;
    session->draw_complete = 0;
}

void	scale(t_ctrl *session, int factor)
{
    if (session->offset.scale + factor > 0)
    {
        session->offset.scale += factor;
        session->draw_complete = 0;
    }
}


void rotate(t_ctrl *session, double angle)
{
    int i;
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);
    t_crd *points = session->map->points;

    for (i = 0; i < session->map->points_len; i++)
    {
        int old_x = points[i].x;
        int old_y = points[i].y;

        points[i].x = old_x * cos_theta - old_y * sin_theta;
        points[i].y = old_x * sin_theta + old_y * cos_theta;
    }
    session->draw_complete = 0; // Force redraw
}
void	flatten_isometrically(t_crd *point)
{
	int	x;
	int y;

	x = (point->x - point->y) * 0.866;
	y = (point->x + point->y) * 0.5 - point->z;

	point->x = x;
	point->y = y;

}

void	apply_offset(t_ctrl *sesh)
{
	int	i;
	int	s;

	i = 0;
	s = sesh->offset.scale;
	while (i < sesh->map->points_len)
	{
		sesh->map->points[i].x = sesh->map->points[i].grid_x * s + sesh->offset.x_offset;
		sesh->map->points[i].y = sesh->map->points[i].grid_y * s + sesh->offset.y_offset;
		sesh->map->points[i].z = sesh->map->points[i].grid_z * sesh->offset.z_scale;
		if (sesh->is_isometric)
			flatten_isometrically(&sesh->map->points[i]);
		i++;
	}
	sesh->draw_complete = 1;
}
