/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/05 22:11:26 by William          ###   ########.fr       */
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
	if (session->draw_complete == 0)
    {
		connect_visible_neighbors(session->image, session->map, GREEN); // Replace GREEN with the desired line color
		mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0);
		session->draw_complete = 1;
	}
    return 0;

}



/* int	render_loop(t_ctrl *session) */
/* { */
/* 	int	i; */

/* 	i = 0; */
/* 	/\* while (i < session->map->points_len) *\/ */
/* 	{ */
/* 		/\* point = session->map->points[i]; *\/ */
/* 		connect_visible_neighbors(session->image, session->map, RED); */
/* 		/\* if (point.visible) *\/ */
/* 		/\* { *\/ */
/* 		/\* 	scale(&point, 30, 30); *\/ */
/* 		/\* 	translate(&point, 100, 100); *\/ */
/* 		/\* 	draw_pixel(session->image, point , RED); *\/ */
/* 		/\* } *\/ */
/* 		i++; */
/* 	} */
/*     mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0); */
/*     return 0; */
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
	session.draw_complete = 0;
    return session;
}

void	clear_screen(t_ctrl *session, int colour)
{
	int	x;
	int y;

	x = 0;
	y = 0;
    while (y < WIN_HEIGHT)
	{
		while (x < WIN_WIDTH)
		{
			t_crd temp = {x, y, 0, 1, 0, 0};
			draw_pixel(session->image, temp , colour);
			x++;
		}
		y++;
	}
	ft_printf("INFO: Screen cleared\n");
}

int main(int argc, char *argv[])
{
    t_ctrl session;
	t_crd	*point;
	t_map	*map;
	int	i;

	i = 0;
    session = init_session();
    if (argc != 2)
	{
        ft_printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
	map = parse_map(argv[1]);
	session.map = map;
    // this is where the scaling happens
	while (i < session.map->points_len)
	{
		point = &session.map->points[i];
		translate(point, -5, -5, 0);
		scale(point, 30, 30, 30);
		flatten_isometrically(point);
		translate(point, WIN_WIDTH/2, WIN_HEIGHT/2, 0);
		i++;

		if (point->x < 0 || point->x >= WIN_WIDTH ||
			point->y < 0 || point->y >= WIN_HEIGHT)
				ft_printf("INFO: Point out of bounds: x=%d, y=%d\n", point->x, point->y);
	}
	print_map_struct(map);
    mlx_loop_hook(session.mlx_ptr, render_loop, &session);

    // Set the key hook (ESC detection)
    mlx_key_hook(session.win_ptr, key_hook, &session);

    // Set the window close event (X button)
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
