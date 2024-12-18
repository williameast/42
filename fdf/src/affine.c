/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:19:40 by William           #+#    #+#             */
/*   Updated: 2024/12/19 00:40:35 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	flatten3d_to_2d(t_crd point, double z_rotation);

void	scale(t_crd *point, int x_scalar, int y_scalar)
{
	point->x *= x_scalar;
	point->y *= y_scalar;
}

void	translate(t_crd *point, int x_scalar, int y_scalar)
{
	point->x += x_scalar;
	point->y += y_scalar;
}

void	rotate_x(t_crd point, double x_rotation);

void	rotate_y(t_crd point, double y_rotation);
