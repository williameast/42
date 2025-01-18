/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:19:40 by William           #+#    #+#             */
/*   Updated: 2025/01/18 11:35:23 by William          ###   ########.fr       */
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

void	flatten_isometrically(t_crd *point)
{
	int	x;
	int	y;

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
