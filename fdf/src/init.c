/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/13 00:56:33 by William          ###   ########.fr       */
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

t_map *init_map()
{
	ft_printf("INFO: initializing map...\n");
    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return NULL;
    map->points = NULL;
    map->points_len = 0;
    map->rows = 0;
    map->cols = 0;
    map->x_min = INT_MAX;
    map->x_max = INT_MIN;
    map->y_min = INT_MAX;
    map->y_max = INT_MIN;
    map->z_min = INT_MAX;
    map->z_max = INT_MIN;
	ft_printf("INFO: initialized map.\n");
    return map;
}
void	init_offset(t_ctrl *session, int x, int y, int z_scalar, int scalar)
{
    session->offset.x_offset = x;
    session->offset.y_offset = y;
    session->offset.scale = scalar;
    session->offset.z_scale = z_scalar;
    session->offset.u = 0.0;
    session->offset.v = 0.0;
    session->draw_complete = 0;
}


/* void	zoom(t_ctrl *session, double zoom_factor) */
/* { */
/*     if (session->offset.scale * zoom_factor > 0) // Prevent non-positive scale */
/*     { */
/*         session->offset.scale *= zoom_factor; */
/*         session->draw_complete = 0; // Trigger a redraw */
/*     } */
/* } */



t_ctrl init_session(void)
{
    t_ctrl session;

    session.mlx_ptr = mlx_init();
    if (!session.mlx_ptr)
    {
        printf("ERROR: Failed to initialize MLX.\n");
        exit(EXIT_FAILURE);
    }
    session.win_ptr = mlx_new_window(session.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, TITLE);
    if (!session.win_ptr)
    {
        printf("ERROR: Failed to create a window.\n");
        exit(EXIT_FAILURE);
    }
    session.image.img_ptr = mlx_new_image(session.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    session.image.addr = mlx_get_data_addr(session.image.img_ptr,
                                           &session.image.bits_per_pixel,
                                           &session.image.line_length,
                                           &session.image.endian);
    session.is_isometric = 1;
    init_offset(&session, -5 , -5, 5, 10);
    center_image(&session);
    /* translate(&session, WIN_WIDTH / 2, WIN_HEIGHT / 2); */
    session.origin = session.offset;
    return (session);
}
