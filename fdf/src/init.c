/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/07 18:51:16 by weast            ###   ########.fr       */
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

t_offset	init_offset(t_crd point, double u, double v)
{
    t_offset	offset;

    offset.value = point;
    offset.scale = 1;
    offset.u = u;
    offset.v = v;
    return (offset);
}

t_ctrl set_state_to_origin(t_ctrl *session)
{
    int	i;
    t_crd *point;

    i = 0;

    while (i < session->map->points_len)
    {
        point = &session->map->points[i];
        translate(point, session->offset);
        scale(point, session->offset);
        flatten_isometrically(point);
        translate(point, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0);

    }




}

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
	session.draw_complete = 0;
    return session;
}
