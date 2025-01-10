/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/10 20:12:39 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void connect_visible_neighbors(t_image image, t_map *map, int color)
{
    for (int i = 0; i < map->points_len; i++) // Iterate over all points
    {
        t_crd current = map->points[i];

        if (!current.visible)
            continue; // Skip non-visible points

        // Check for a right neighbor (same row)
        if (current.grid_x + 1 < map->cols)
        {
            int right_index = i + 1; // Index of the right neighbor
            if (map->points[right_index].visible)
                draw_line(image, current, map->points[right_index], color);
			ft_printf("INFO: inside right neighbour check\n");
        }

        // Check for a bottom neighbor (next row)
        if (current.grid_y + 1 < map->rows)
        {
            int bottom_index = i + map->cols; // Index of the bottom neighbor
            if (map->points[bottom_index].visible)
                draw_line(image, current, map->points[bottom_index], color);
			ft_printf("INFO: inside bottom neighbour check\n");
        }
    }
}


int render_loop(t_ctrl *session)
{
	if (!session->draw_complete)
    {
		clear_image(session, WIN_WIDTH, WIN_HEIGHT);
		apply_offset(session);
		connect_visible_neighbors(session->image, session->map, GREEN); // Replace GREEN with the desired line color
		mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0);
		session->draw_complete = 1;
		ft_printf("INFO: render cycle complete.\n");
	}
    return 0;
}


int main(int argc, char *argv[])
{
    t_ctrl session;
	t_map	*map;

    session = init_session();
    if (argc != 2)
	{
        ft_printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
	map = parse_map(argv[1]);
	session.map = map;
	print_map_struct(map);
    mlx_loop_hook(session.mlx_ptr, render_loop, &session);
    mlx_key_hook(session.win_ptr, key_hook, &session);
    mlx_hook(session.win_ptr, 17, 0, close_window, &session); // 17 is the event for the 'X' button
    mlx_loop(session.mlx_ptr);
    if (!map)
    {
        ft_printf("ERROR: Error loading map.\n");
        return 1;
    }
	free_map(map);
    return 0;
}
