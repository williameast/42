/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:14:30 by William           #+#    #+#             */
/*   Updated: 2024/12/15 23:15:12 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void	ft_put_pixel(t_graphics *gfx, t_crd crd, int colour)
{
    char *pxl;
    int buffer_index = gfx->active_buffer;

    if (crd.x >= 0 && crd.x < WIN_WIDTH && crd.y >= 0 && crd.y < WIN_HEIGHT)
    {
        pxl = gfx->addr[buffer_index] + (crd.y * gfx->line_length + crd.x * (gfx->bits_per_pixel) / 8);
        *(unsigned int *)pxl = colour;
    }
}
