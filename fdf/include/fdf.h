/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:47 by weast             #+#    #+#             */
/*   Updated: 2024/12/12 14:26:33 by William          ###   ########.fr       */
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
    int	z;
	int	visible;
}			t_crd;

typedef struct s_map {
    t_crd	*points;
	int	rows;
	int	cols;
}			t_map;

/* declarations */
/* Declarations from parsing.c */
int main(int argc, char **argv);

/* Declarations from utils.c */
int	check_extension(char *filename, char *ext);
void	free_char_array(char **array);
void	free_int_array(int *array);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);

/* Declarations from init.c */
t_map *init_map(void);

/* Declarations from printing.c */
void	print_point(t_crd c);
void	print_map_struct(t_map *map);
void	print_coordinates(t_crd *crd, int count);
void	print_map(t_map *map);

/* Declarations from map_mgmt.c */
t_crd populate_coordinate(int x, int y, char *z);
char *read_full_map_as_str(char *file);
t_crd *parse_row_to_coordinates(char *row, int y, int *count);
t_map *initialize_map();
void	free_map(t_map *map);
int append_row_to_map(t_map *map, t_crd *row_coords, int row_count);
t_map *parse_map(char *filename);

/* declarations end */



#endif // FDF_H
