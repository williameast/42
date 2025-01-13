/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:41:17 by William           #+#    #+#             */
/*   Updated: 2025/01/13 00:58:44 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fdf.h"

static void check_and_draw_right_neighbor(t_image image, t_map *map, t_crd current, int color, int i)
{
	int	j;

	j = i + 1;
	while (j < map->points_len)
    {
        if (map->points[j].grid_y == current.grid_y &&
            map->points[j].grid_x == current.grid_x + 1)
        {
            if (map->points[j].visible)
                draw_line(image, current, map->points[j], color);
            break;
        }
		j++;
    }
}

static void check_and_draw_bottom_neighbor(t_image image, t_map *map, t_crd current, int color, int i)
{
	int	j;

	j = i + 1;
	while (j < map->points_len)
    {
        if (map->points[j].grid_x == current.grid_x &&
            map->points[j].grid_y == current.grid_y + 1)
        {
            if (map->points[j].visible)
                draw_line(image, current, map->points[j], color);
            break;
        }
		j++;
    }
}

static void connect_visible_neighbors(t_image image, t_map *map, int color)
{
	int	i;
	t_crd	current;

	i = 0;


	while (i < map->points_len)
    {
        current = map->points[i];
        if (!current.visible)
            continue;
        check_and_draw_right_neighbor(image, map, current, ternary(current.grid_z < 0, RED, color), i);
        check_and_draw_bottom_neighbor(image, map, current, ternary(current.grid_z < 0, RED, color), i);
		i++;
    }
}

void	center_image(t_ctrl *session)
{
	int	dx;
	int	dy;

	dx = session->map->x_max - session->map->x_min;
	dy = session->map->y_max - session->map->y_min;
	session->offset.x_offset = (WIN_WIDTH / 2) - (dx * session->offset.scale / 2);
	session->offset.y_offset = (WIN_HEIGHT / 2) - (dy * session->offset.scale / 2);
	session->draw_complete = 0;
	if (DEBUG)
	{
		ft_printf("INFO: (min, max) x (%i, %i), y (%i, %i)", session->map->x_min, session->map->x_max, session->map->y_min, session->map->y_max);
		ft_printf("INFO: centering values: dx,dy (%i, %i)\n", dx, dy);
		print_offset(session->offset);
	}
}

int render_loop(t_ctrl *session)
{
	if (!session->draw_complete)
    {
		clear_image(session, WIN_WIDTH, WIN_HEIGHT);
		apply_offset(session);
		connect_visible_neighbors(session->image, session->map, GREEN);
		mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0);
		session->draw_complete = 1;
		if (DEBUG)
			ft_printf("INFO: render cycle complete.\n");
	}
    return 0;
}
