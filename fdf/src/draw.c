/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:14:30 by William           #+#    #+#             */
/*   Updated: 2025/01/07 15:19:33 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"



void draw_pixel(t_image image, t_crd point, int color)
{
    char *pixel;
    if (!is_pixel_out_of_bounds(point))
    {
        pixel = image.addr + (point.y * image.line_length + point.x * (image.bits_per_pixel / 8));
        *(int *)pixel = color;
    }
    else
        ft_printf("INFO: pixel (%i, %i) out of bounds. skipping...\n", point.x, point.y);
}


void	draw_line(t_image image, t_crd src, t_crd dest, int colour)
{
    int	e2;
    t_line	line;

    line = init_line(src, dest, colour);
    while (1)
    {
        draw_pixel(image, line.src, line.colour);
        if (line.src.x == line.dest.x && line.src.y == line.dest.y)
            break;
        e2 = line.error * 2;
        if (e2 > -line.dy)
        {
            line.error -= line.dy;
            line.src.x += line.step_x;
        }
        if (e2 < line.dx)
        {
            line.error += line.dx;
            line.src.y += line.step_y;
        }
    }
}

