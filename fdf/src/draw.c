/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:14:30 by William           #+#    #+#             */
/*   Updated: 2024/12/16 18:29:26 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


// RGBa pixel encoder on 1d char array.
// TODO add out of bounds check.
void	draw_pixel(char *data, t_crd point, int colour, int stride)
{
    int	offset;

    offset =  (4 * point.x) + (point.y * stride);
    data[offset] = colour & 0xFF; // b
    data[offset + 1] = (colour >> 8) & 0xFF; // g
    data[offset + 2] = (colour >> 16) & 0xFF; // r
    data[offset + 3] = (colour >> 24) & 0xFF; // alpha
}

int	derivative_of(int a, int b)
{
    return(abs(a - b));
}

int	pos_or_neg(int a, int b)
{
    if (a < b)
        return (1);
    return (-1);
}


// might need an init function to avoid norminette.
void	draw_line(char *data, t_crd src, t_crd dest, int colour, int stride)
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
        draw_pixel(data, src, colour, stride);
        if (src.x == dest.x && src.y == dest.y)
            break;
        if ((error * 2)> -d.y)
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
