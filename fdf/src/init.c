/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/07 15:19:54 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// unused currently.
t_crd	handle_out_of_bounds_line(t_crd point)
{
    t_crd	out;

    out = point;
    if (is_pixel_out_of_bounds(point))
    {
        if (CLAMP)
        {
            if (point.x < 0)
                out.x = 0;
            if (point.y < 0)
                out.y = 0;
            if (point.x >= WIN_WIDTH)
                out.x = WIN_WIDTH - 1;
            if (point.y >= WIN_HEIGHT)
                out.y = WIN_HEIGHT - 1;
        }
        else
        {
            out.visible = 0;
        }
    }
    return (out);
}


t_line	init_line(t_crd src, t_crd dest, int colour)
{
    t_line	line;

    line.src = handle_out_of_bounds_line(src);
    line.dest = handle_out_of_bounds_line(dest);
    line.dx = abs(line.dest.x - line.src.x);
    line.dy = abs(line.dest.y - line.src.y);
    line.step_x = ternary(line.src.x < line.dest.x, 1, -1);
    line.step_y = ternary(line.src.y < line.dest.y, 1, -1);
    line.error = line.dx - line.dy;
    line.colour = colour;
    line.visible = 1;
    return (line);
}
