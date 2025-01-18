/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:41:17 by William           #+#    #+#             */
/*   Updated: 2025/01/18 13:48:31 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	connect_right_node(t_image image, t_map *map, t_crd current, int i)
{
	int			j;
	t_primitive	obj;

	j = i + 1;
	obj.a = map->z_min;
	obj.b = map->z_max;
	while (j < map->points_len)
	{
		if (map->points[j].grid_y == current.grid_y
			&& map->points[j].grid_x == current.grid_x + 1)
		{
			if (map->points[j].visible)
				draw_line(image, current, map->points[j], obj);
			break ;
		}
		j++;
	}
}

static void	connect_bottom_node(t_image image, t_map *map, t_crd current, int i)
{
	int			j;
	t_primitive	obj;

	j = i + 1;
	obj.a = map->z_min;
	obj.b = map->z_max;
	while (j < map->points_len)
	{
		if (map->points[j].grid_x == current.grid_x
			&& map->points[j].grid_y == current.grid_y + 1)
		{
			if (map->points[j].visible)
				draw_line(image, current, map->points[j], obj);
			break ;
		}
		j++;
	}
}

static void	connect_visible_nodes(t_image image, t_map *map)
{
	int		i;
	t_crd	current;

	i = 0;
	while (i < map->points_len)
	{
		current = map->points[i];
		if (!current.visible)
			continue ;
		connect_right_node(image, map, current, i);
		connect_bottom_node(image, map, current, i);
		i++;
	}
}

void	center_image(t_ctrl *se)
{
	int		dx;
	int		dy;
	float	scale_x;
	float	scale_y;

	dx = se->map->x_max - se->map->x_min;
	dy = se->map->y_max - se->map->y_min
		+ (se->map->z_max - se->map->z_min) * se->offset.z_scale;
	if (dx == 0)
		dx = 1;
	if (dy == 0)
		dy = 1;
	scale_x = (float) WIN_WIDTH / dx;
	scale_y = (float) WIN_HEIGHT / dy;
	if (scale_x < scale_y)
		se->offset.scale = scale_x;
	else
		se->offset.scale = scale_y;
	se->offset.x_offset = (WIN_WIDTH / 2)
		- ((se->map->x_max + se->map->x_min) * se->offset.scale / 2);
	se->offset.y_offset = (WIN_HEIGHT / 2)
		- ((se->map->y_max + se->map->y_min
				+ (se->map->z_max + se->map->z_min) * se->offset.z_scale)
			* se->offset.scale / 2);
}

int	render_loop(t_ctrl *session)
{
	if (!session->draw_complete)
	{
		clear_image(session, WIN_WIDTH, WIN_HEIGHT);
		apply_offset(session);
		connect_visible_nodes(session->image, session->map);
		mlx_put_image_to_window(session->mlx_ptr,
			session->win_ptr,
			session->image.img_ptr, 0, 0);
		session->draw_complete = 1;
		if (DEBUG)
			ft_printf("INFO: render cycle complete.\n");
	}
	return (0);
}
