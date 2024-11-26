/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:55:50 by weast             #+#    #+#             */
/*   Updated: 2024/11/26 17:36:32 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define	WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


/* void	my_mlx_pixel_put(t_data *data, int x, int y, int color) */
/* { */
/* 	char	*dst; */

/* 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)); */
/* 	*(unsigned int*)dst = color; */
/* } */


/* int	main(void) */
/* { */
/* 	void	*mlx; */
/* 	void	*mlx_win; */
/* 	t_data	img; */

/* 	mlx = mlx_init(); */
/* 	mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!"); */
/* 	img.img = mlx_new_image(mlx, 800, 600); */
/* 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, */
/* 								&img.endian); */
/* 	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); */
/* 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); */
/* 	mlx_loop(mlx); */
/*     /\* read_something(); *\/ */
/* } */

int	rgb_to_int(double r, double g, double b)
{
  int	out;

  out = 0;
  out |= (int)(b * 255);
  out |= (int)(g * 255) << 8;
  out |= (int)(r * 255) << 16;
  return (out);
}


void ft_put_pixel(t_data *data, int x, int y, int color)
{
    char *pxl;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        pxl = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}

void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    int step;
    int x;
    int y;
    int i;
    int delta_x;
    int delta_y;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    if (abs(delta_x) >= abs(delta_y))
        step = abs(delta_x);
    else
        step = abs(delta_y);
    delta_x = delta_x / step;
    delta_y = delta_y / step;
    x = x1;
    y = x2;
    i = 0;
    while (i < step)
    {
        ft_put_pixel(data, x, y, color);
        x += delta_x;
        y += delta_y;
        i++;
    }
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
  ft_draw_line(&img, 10, 10,200, 200, 0xFFFFFF);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
