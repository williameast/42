/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:46:04 by William           #+#    #+#             */
/*   Updated: 2025/01/18 11:57:55 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	interpolate(int start, int end, float proportion)
{
	int	r;
	int	g;
	int	b;

	r = ((start >> 16) & 0xFF)
		+ proportion
		* (((end >> 16) & 0xFF)
			- ((start >> 16) & 0xFF));
	g = ((start >> 8) & 0xFF)
		+ proportion
		* (((end >> 8) & 0xFF)
			- ((start >> 8) & 0xFF));
	b = (start & 0xFF)
		+ proportion
		* ((end & 0xFF)
			- (start & 0xFF));
	return (((r << 16) | (g << 8) | b));
}

static float	clamp_proportion(float proportion)
{
	if (proportion < 0.0f)
		return (0.0f);
	if (proportion > 1.0f)
		return (1.0f);
	return (proportion);
}

int	get_colour(float z, int z_min, int z_max)
{
	float	proportion;
	float	z_range;

	if (z_max == z_min)
		return (0x0000FF);
	z_range = (float)(z_max - z_min);
	proportion = clamp_proportion((z - z_min) / z_range);
	return (interpolate(0x0000FF, 0xFF0000, proportion));
}
