/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:41:17 by William           #+#    #+#             */
/*   Updated: 2025/01/17 13:59:57 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fdf.h"

static void check_and_draw_right_neighbor(t_image image, t_map *map, t_crd current, int i)
{
	int	j;

	j = i + 1;
	while (j < map->points_len)
    {
        if (map->points[j].grid_y == current.grid_y &&
            map->points[j].grid_x == current.grid_x + 1)
        {
            if (map->points[j].visible)
                draw_line(image, current, map->points[j], map->z_min, map->z_max);
            break;
        }
		j++;
    }
}

static void check_and_draw_bottom_neighbor(t_image image, t_map *map, t_crd current, int i)
{
	int	j;

	j = i + 1;
	while (j < map->points_len)
    {
        if (map->points[j].grid_x == current.grid_x &&
            map->points[j].grid_y == current.grid_y + 1)
        {
            if (map->points[j].visible)
                draw_line(image, current, map->points[j], map->z_min, map->z_max);
            break;
        }
		j++;
    }
}

static void connect_visible_neighbors(t_image image, t_map *map)
{
	int	i;
	t_crd	current;

	i = 0;


	while (i < map->points_len)
    {
        current = map->points[i];
        if (!current.visible)
            continue;
        check_and_draw_right_neighbor(image, map, current, i);
        check_and_draw_bottom_neighbor(image, map, current, i);
		i++;
    }
}

void	center_image(t_ctrl *session)
{
	int		dx, dy;
	float	scale_x, scale_y;

	dx = session->map->x_max - session->map->x_min;

	// Include z_scale in dy calculation
	dy = session->map->y_max - session->map->y_min +
		(session->map->z_max - session->map->z_min) * session->offset.z_scale;

	// Avoid division by zero
	if (dx == 0) dx = 1;
	if (dy == 0) dy = 1;

	scale_x = (float)WIN_WIDTH / dx;
	scale_y = (float)WIN_HEIGHT / dy;

	// Choose the smaller scale to fit the entire map
	session->offset.scale = (scale_x < scale_y) ? scale_x : scale_y;

	// Correct offsets using midpoints
	session->offset.x_offset = (WIN_WIDTH / 2) -
		((session->map->x_max + session->map->x_min) * session->offset.scale / 2);
	session->offset.y_offset = (WIN_HEIGHT / 2) -
		((session->map->y_max + session->map->y_min +
		(session->map->z_max + session->map->z_min) * session->offset.z_scale) * session->offset.scale / 2);

	translate(session, WIN_WIDTH / 2, 0 );
	/* translate(session, 0, WIN_HEIGHT / 2 ); */
	session->draw_complete = 0;

	if (DEBUG)
	{
		ft_printf("DEBUG: Map bounds - x_min: %d, x_max: %d, y_min: %d, y_max: %d, z_min: %d, z_max: %d\n",
			session->map->x_min, session->map->x_max,
			session->map->y_min, session->map->y_max,
			session->map->z_min, session->map->z_max);
		ft_printf("DEBUG: dx: %d, dy: %d, scale: %f\n", dx, dy, session->offset.scale);
		ft_printf("DEBUG: Offsets - x_offset: %d, y_offset: %d\n",
			session->offset.x_offset, session->offset.y_offset);
	}
}

int render_loop(t_ctrl *session)
{
	if (!session->draw_complete)
    {
		clear_image(session, WIN_WIDTH, WIN_HEIGHT);
		apply_offset(session);
		connect_visible_neighbors(session->image, session->map);
		mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0);
		session->draw_complete = 1;
		if (DEBUG)
			ft_printf("INFO: render cycle complete.\n");
	}
    return 0;
}
