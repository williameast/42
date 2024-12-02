/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:47 by weast             #+#    #+#             */
/*   Updated: 2024/12/02 21:05:58 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

/* internal includes */
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/ft_printf/ft_printf.h"

/* standard lib stuff */
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>


#define	WIN_WIDTH 640
#define 	WIN_HEIGHT 640
#define	GREEN  0x00FF00
#define	RED  0xFF0000
#define	BLUE  0x0000FF

/* stuctures */
typedef struct s_graphics {
    void *mlx_ptr;         // Connection instance
    void *win_ptr;         // Window instance
    void *buffer[2];       // Two image buffers for double buffering
    char *addr[2];         // Memory addresses of the buffers
    int bits_per_pixel;    // Bits per pixel
    int line_length;       // Bytes per row
    int endian;            // Endian type
    int active_buffer;     // Tracks the currently active buffer
} t_graphics;


typedef struct s_crd {
	int	x;
	int	y;
}			t_crd;

/* declarations */
/* Declarations from read_file.c */
int read_something(void);
int	check_extension(char *filename, char *ext);

/* Declarations from test.c */
void	ft_put_pixel(t_graphics *gfx, t_crd crd, int colour);
t_crd	init_crd(int x, int y);
void draw_rectangle1(t_graphics *gfx, t_crd start, int width, int height, int color);
void	swap_buffers(t_graphics *gfx);
int render(void *param);
int main();

/* declarations end */



#endif // FDF_H
