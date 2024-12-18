/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2024/12/18 21:25:34 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* int main(int argc, char **argv) */
/* { */
/* 	t_map	*map; */

/*     if (argc != 2) */
/*     { */
/*         ft_printf("Usage: %s <filename>\n", argv[0]); */
/*         return 1; */
/*     } */
/* 	map = parse_map(argv[1]); */
/* 	print_map_struct(map); */
/*     if (!map) */
/*     { */
/*         ft_printf("ERROR: Error loading map.\n"); */
/*         return 1; */
/*     } */
/* 	free_map(map); */
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
    session.win_ptr = mlx_new_window(session.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Moving Lines");
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

int render_loop(t_ctrl *session)
{
    static int offset = 0;
    t_crd start = {100 + offset, 100, 0, 1};
    t_crd end = {200 + offset, 300, 0, 1};

    // Clear the image by filling it with black
    for (int y = 0; y < WIN_HEIGHT; y++)
        for (int x = 0; x < WIN_WIDTH; x++)
		{
			t_crd temp = {x, y, 0, 1};
			draw_pixel(session->image, temp , 0x000000);
		}

    // Draw the moving line
    draw_line(session->image, start, end, 0xFF0000); // Red color

    // Update the offset for animation
    offset = (offset + 2) % WIN_WIDTH;

    // Display the image
    mlx_put_image_to_window(session->mlx_ptr, session->win_ptr, session->image.img_ptr, 0, 0);

    return 0;
}

int main()
{
    t_ctrl session;

    session = init_session();

    // Set up the render loop
    mlx_loop_hook(session.mlx_ptr, render_loop, &session);
    mlx_loop(session.mlx_ptr);

    return 0;
}
