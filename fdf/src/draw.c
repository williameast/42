/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:14:30 by William           #+#    #+#             */
/*   Updated: 2025/01/05 20:38:46 by William          ###   ########.fr       */
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
        ft_printf("INFO: pixel (%i, %i) out of bounds. skipping...\n", point.x, point.y);
}

// might need an init function to avoid norminette.
/* void	draw_line(t_image image, t_crd src, t_crd dest, int colour) */
/* { */
/*     t_crd d; */
/*     t_crd s; */
/*     int	error; */

/*     ft_printf("INFO: drawing line from (%i, %i)  to (%i, %i)\n", src.x, src.y, dest.x, dest.y); */

/*     d.x = derivative_of(dest.x, src.x); */
/*     d.y = derivative_of(dest.y, src.y); */
/*     s.x = pos_or_neg(src.x, dest.x); */
/*     s.y = pos_or_neg(src.y, dest.y); */
/*     error = d.x - d.y; */
/*     while(1) */
/*     { */
/*         draw_pixel(image, src, colour); */
/*         if (src.x >= 0 && src.x < WIN_WIDTH && src.y >= 0 && src.y < WIN_HEIGHT) */
/*             break; */
/*         if ((error * 2) > -d.y) */
/*         { */
/*             error -= d.y; */
/*             src.x += s.x; */
/*         } */
/*         if ((error * 2) < d.x) */
/*         { */
/*             error += d.x; */
/*             src.y += s.y; */
/*         } */
/*     } */
/* } */

void draw_line(t_image image, t_crd src, t_crd dest, int color)
{
    t_crd d;
    t_crd s;
    int error;

    /* ft_printf("INFO: drawing line from (%i, %i) to (%i, %i)\n", src.x, src.y, dest.x, dest.y); */

    // Check if the source and destination are valid
    if (src.x < 0 || src.y < 0 || dest.x < 0 || dest.y < 0 ||
        src.x >= WIN_WIDTH || src.y >= WIN_HEIGHT ||
        dest.x >= WIN_WIDTH || dest.y >= WIN_HEIGHT)
    {
        ft_printf("WARNING: Skipping invalid line (%i, %i) to (%i, %i)\n", src.x, src.y, dest.x, dest.y);
        return;
    }

    // Calculate deltas and steps
    d.x = abs(dest.x - src.x);
    d.y = abs(dest.y - src.y);
    s.x = (src.x < dest.x) ? 1 : -1;
    s.y = (src.y < dest.y) ? 1 : -1;
    error = d.x - d.y;

    // Bresenham's line algorithm
    while (1)
    {
        // Draw pixel if within bounds
        if (src.x >= 0 && src.x < WIN_WIDTH && src.y >= 0 && src.y < WIN_HEIGHT)
        {
            draw_pixel(image, src, color);
        }
        else
        {
            ft_printf("INFO: Pixel (%i, %i) out of bounds. Skipping...\n", src.x, src.y);
        }

        // Break when destination is reached
        if (src.x == dest.x && src.y == dest.y)
        {
            ft_printf("INFO: line (%i, %i) reached destination. breaking...\n", src.x, src.y);
            break;
        }

        // Update error and coordinates
        int e2 = error * 2;

        if (e2 > -d.y)
        {
            error -= d.y;
            src.x += s.x;
        }
        if (e2 < d.x)
        {
            error += d.x;
            src.y += s.y;
        }
    }
}
