/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:19:40 by William           #+#    #+#             */
/*   Updated: 2025/01/14 17:44:21 by weast            ###   ########.fr       */
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


void	rotate(t_crd *point, double angle)
{
	int	x;
	int	y;
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);

	x = point->x * cos_theta - point->y * sin_theta;
	y = point->x * sin_theta + point->y * cos_theta;
	point->x = x;
	point->y = y;
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

void	flatten_cabinet(t_crd *point)
{
	int	x;
	int	y;

	x = point->x + point->z * 0.5;
	y = point->y - point->z * 0.5;
	point->x = x;
	point->y = y;
}


void	apply_offset(t_ctrl *sesh)
{
	int		i;
	t_offset		offset;
	t_crd	*point;

	i = 0;
	offset = sesh->offset;
	while (i < sesh->map->points_len)
	{
		point = &sesh->map->points[i];
		point->x = point->grid_x * offset.scale + offset.x_offset;
		point->y = point->grid_y * offset.scale + offset.y_offset;
		point->z = point->grid_z * offset.z_scale * offset.scale;
		if (sesh->is_isometric == 1)
			flatten_isometrically(point);
		else if (sesh->is_isometric == -1)
			flatten_cabinet(point);
		if (offset.rotation_changed)
			rotate(point, offset.rotation);
		i++;
	}
	sesh->draw_complete = 1;
	offset.rotation_changed = 0;
}
