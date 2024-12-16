/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2024/12/16 18:26:16 by William          ###   ########.fr       */
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

void	init_graphics(t_graphics *gfx, int width, int height, char *title)
{
	gfx->mlx_ptr = mlx_init();
	if (!gfx->mlx_ptr)
	{
		ft_printf("ERROR: failed to init MLX.\n");
		return ;
	}
	gfx->win_ptr = mlx_new_window(gfx->mlx_ptr, width, height, title);
	if (!gfx->win_ptr)
	{
		ft_printf("ERROR: failed to create window.\n");
		return ;
	}
	gfx->buffer = mlx_new_image(gfx->mlx_ptr, width, height);
	if (!gfx->buffer)
	{
		ft_printf("ERROR: failed to create buffer for image.\n");
		return ;
	}
	gfx->addr = mlx_get_data_addr(gfx->buffer, &gfx->bits_per_pixel, &gfx->line_length, &gfx->endian);
	gfx->active_buffer = 0;
}

int main()
{
	t_graphics gfx;
	t_crd start, end;
	init_graphics(&gfx, WIN_WIDTH, WIN_HEIGHT, "doodlin");

	start = (t_crd) {100, 100, 1, 1};
	end = (t_crd) {200, 325, 1, 1};

    draw_line(gfx.addr, start, end, 0xFF0000, gfx.line_length);  // Red Line

    mlx_put_image_to_window(gfx.mlx_ptr, gfx.win_ptr, gfx.buffer, 0, 0);
    mlx_loop(gfx.mlx_ptr);
    return 0;
}
