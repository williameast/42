/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:14:30 by William           #+#    #+#             */
/*   Updated: 2025/01/17 14:47:52 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"



void	draw_pixel(t_image image, t_crd point, int color)
{
    char *pixel;
    if (!is_pixel_out_of_bounds(point))
    {
        pixel = image.addr + (point.y * image.line_length + point.x * (image.bits_per_pixel / 8));
        *(int *)pixel = color;
    }
    else if (DEBUG)
        ft_printf("INFO: pixel (%i, %i) out of bounds. skipping...\n", point.x, point.y);
}


void	draw_line(t_image image, t_crd src, t_crd dest, int z_min, int z_max)
{
    int	e2;
    t_line	line;

    if (is_pixel_out_of_bounds(src) && is_pixel_out_of_bounds(dest))
        return ;
    line = init_line(src, dest);
    while (1)
    {
        draw_pixel(image, line.src, get_colour_gradient(line.current_z, z_min, z_max));
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
        line.current_z += line.z_increment;
    }
}

void	clear_image(t_ctrl *session, int width, int height)
{
    if (session->image.img_ptr)
        mlx_destroy_image(session->mlx_ptr, session->image.img_ptr);
    session->image.img_ptr = mlx_new_image(session->mlx_ptr, width, height);
    session->image.addr = mlx_get_data_addr(session->image.img_ptr,
                                            &session->image.bits_per_pixel,
                                            &session->image.line_length,
                                            &session->image.endian);
    if (DEBUG)
        ft_printf("INFO: Image cleared and reinitialized.\n");
}
