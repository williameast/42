/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2025/01/05 16:29:43 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void connect_visible_neighbors(t_image image, t_map *map, int color)
{
    for (int y = 0; y < map->rows; y++)
    {
        for (int x = 0; x < map->cols; x++)
        {
            int index = y * map->cols + x; // Index of the current point

            if (!map->points[index].visible )
                continue; // Skip if the current point is not visible

            // Connect to the right neighbor if visible
            if (x + 1 < map->cols && map->points[index + 1].visible)
                draw_line(image, map->points[index], map->points[index + 1], color);

            // Connect to the down neighbor if visible
            if (y + 1 < map->rows && map->points[index + map->cols].visible)
                draw_line(image, map->points[index], map->points[index + map->cols], color);
        }
    }
}
/* int render_loop(t_ctrl *session) */
/* { */
/*     /\* connect_visible_neighbors(session->image, session->map, RED); // Red lines *\/ */
/*     mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0); */
/*     return 0; */
/* } */
int render_loop(t_ctrl *session)
{
    int i;
    t_crd *point;

    // Loop through each point in the map
    for (i = 0; i < session->map->rows * session->map->cols; i++)
    {
        point = &session->map->points[i];
        if (point->visible) // Only draw visible points
        {
            draw_pixel(session->image, *point, RED); // Replace RED with the desired color
        }
    }

    mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0);
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
			t_crd temp = {x, y, 0, 1};
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
	}
	print_map_struct(map);
    mlx_loop_hook(session.mlx_ptr, render_loop, &session);
    mlx_loop(session.mlx_ptr);
    if (!map)
    {
        ft_printf("ERROR: Error loading map.\n");
        return 1;
    }
	free_map(map);
    return 0;
}
