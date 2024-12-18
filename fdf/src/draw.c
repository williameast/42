/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:14:30 by William           #+#    #+#             */
/*   Updated: 2024/12/18 21:29:59 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"



void draw_pixel(t_image image, t_crd point, int color)
{
    char *pixel;
    if (point.x >= 0 && point.x < WIN_WIDTH && point.y >= 0 && point.y < WIN_HEIGHT)
    {
        pixel = image.addr + (point.y * image.line_length + point.x * (image.bits_per_pixel / 8));
        *(int *)pixel = color;
    }
    else
        ft_printf("WARN: attempted to draw pixel out of bounds.\n");
}

// might need an init function to avoid norminette.
void	draw_line(t_image image, t_crd src, t_crd dest, int colour)
{
    t_crd d;
    t_crd s;
    int	error;

    d.x = derivative_of(dest.x, src.x);
    d.y = derivative_of(dest.y, src.y);
    s.x = pos_or_neg(src.x, dest.x);
    s.y = pos_or_neg(src.y, dest.y);
    error = d.x - d.y;
    while(1)
    {
        draw_pixel(image, src, colour);
        if (src.x == dest.x && src.y == dest.y)
            break;
        if ((error * 2) > -d.y)
        {
            error -= d.y;
            src.x += s.x;
        }
        if ((error * 2) < d.x)
        {
            error += d.x;
            src.y += s.y;
        }
    }
}

