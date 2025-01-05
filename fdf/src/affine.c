/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:19:40 by William           #+#    #+#             */
/*   Updated: 2025/01/05 11:52:21 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*       what would it look like to calculate the sin and cosin before?       */
/*                                                                            */
/* ************************************************************************** */


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

/* static void	rotate_x(t_crd point, double sin_rotation, double cos_rotation); */
/* { */
/* 	int	new_y; */
/* 	int new_z; */

/* 	new_y = point.y * cos_rotation + point.z * sin_rotation; */
/* 	new_z = -point.y * sin_rotation + point.z * cos_rotation; */
/* 	point.y = new_y; */
/* 	point.z = new_z; */
/* } */

/* static void	rotate_y(t_crd point, double sin_rotation, double cos_rotation); */
/* { */
/* 	int	new_x; */
/* 	int new_z; */

/* 	new_x = point.x * cos_rotation + point.z * sin_rotation; */
/* 	new_z = -point.x * sin_rotation + point.z * cos_rotation; */
/* 	point.x = new_x; */
/* 	point.z = new_z; */
/* } */


/* void	convert_iso(t_crd point, double cos_iso, double sin_iso) */
/* { */
/* 	int	x; */
/* 	int y; */

/* 	x = (point.x - point.y) * cos_iso; */
/* 	y = -point.z + (x + point.y)  * sin_iso; */

/* 	point.x = x; */
/* 	point.y = y; */

/* } */

void	convert_iso(t_crd point, double cos_iso, double sin_iso)
{
	int	x;
	int y;

	x = (point.x - point.y) * cos_iso;
	y = -point.z + (x + point.y)  * sin_iso;

	point.x = x;
	point.y = y;

}
