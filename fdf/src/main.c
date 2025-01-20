/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/20 12:46:32 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	apply_offset(t_ctrl *sesh)
{
	int			i;
	t_offset	offset;
	t_crd		*point;

	i = 0;
	offset = sesh->offset;
	while (i < sesh->map->points_len)
	{
		point = &sesh->map->points[i];
		point->x = point->grid_x * offset.scale + offset.x_offset;
		point->y = point->grid_y * offset.scale + offset.y_offset;
		point->z = point->grid_z * offset.z_scale * offset.scale;
		if (sesh->is_isometric == 1)
			flatten_isometrically(point);
		else if (sesh->is_isometric == -1)
			flatten_cabinet(point);
		i++;
	}
	sesh->draw_complete = 1;
}

static void	attach_mlx(t_ctrl *session)
{
	mlx_loop_hook(session->mlx_ptr, render_loop, session);
	mlx_key_hook(session->win_ptr, key_hook, session);
	mlx_hook(session->win_ptr, 17, 0, close_window, session);
	mlx_loop(session->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_ctrl	session;
	t_map	*map;

	if (argc != 2)
		return (ft_printf("Usage: %s <filename>\n", argv[0]));
	map = parse_map(argv[1]);
	if (!map)
		return (ft_printf("ERROR: Error loading map.\n"));
	session = init_session(map);
	center_image(&session);
	translate(&session, WIN_WIDTH / 2, 0);
	session.draw_complete = 0;
	if (DEBUG)
		print_map_struct(map);
	if (RENDER)
		attach_mlx(&session);
	free_map(map);
	return (0);
}
