/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:19:40 by William           #+#    #+#             */
/*   Updated: 2025/01/10 20:06:55 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*       what would it look like to calculate the sin and cosin before?       */
/*                                                                            */
/* ************************************************************************** */


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

void	reset_session(t_ctrl *session)
{
	int	i;

	i = 0;
	while (i < session->map->points_len)
	{
		session->map->points[i].x = session->map->points[i].grid_x;
		session->map->points[i].y = session->map->points[i].grid_y;
		session->map->points[i].z = session->map->points[i].grid_z;
		i++;
	}
	session->offset = session->origin;
	ft_printf("INFO: resetting to original state.\n");
}

