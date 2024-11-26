/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:55:50 by weast             #+#    #+#             */
/*   Updated: 2024/11/26 15:45:57 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


#include <stdio.h>
#include <fcntl.h>
#include <mlx.h>

int read_something(void)
{
  int    fd;
  char  *next_line;
  int  count;

  count = 0;
  fd = open("example.txt", O_RDONLY);
  while (1)
  {
    next_line = get_next_line(fd);
    if (next_line == NULL)
        break ;
    count++;
    ft_printf("we here");
    ft_printf("[%d]:%s\n", count, next_line);
    next_line = NULL;
  }
  close(fd);
  return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int	main(void)
{
	/* void	*mlx; */
	/* void	*mlx_win; */
	/* t_data	img; */

	/* mlx = mlx_init(); */
	/* mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!"); */
	/* img.img = mlx_new_image(mlx, 800, 600); */
	/* img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, */
	/* 							&img.endian); */
	/* my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); */
	/* mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); */
	/* mlx_loop(mlx); */
    read_something();
}
