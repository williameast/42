/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:47 by weast             #+#    #+#             */
/*   Updated: 2025/01/05 22:06:25 by William          ###   ########.fr       */
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
#define 	TITLE "Wire mesh render"

#define	GREEN  0x00FF00
#define	RED  0xFF0000
#define	BLUE  0x0000FF
#define	COS30  0.866025
#define	SIN30 0.5

typedef struct s_crd {
	int	x;
	int	y;
    int	z;
	int grid_x;
	int grid_y;
	int	visible;
}			t_crd;

typedef struct s_map {
    t_crd	*points;
	int		points_len;
	int		rows;
	int		cols;
	int 	z_max;
	int 	z_min;
}			t_map;

typedef struct s_image {
	void	*img_ptr;
	char 	*addr;
	int		bits_per_pixel;
	int 	line_length;
	int 	endian;
}			t_image;

typedef struct s_ctrl {
	/* double			scale; */
	/* double			z_scale; */
	void			*mlx_ptr;
	void			*win_ptr;
	t_map			*map;
	t_image			image;
	int				draw_complete;
}			t_ctrl;




/* declarations */
/* Declarations from controls.c */
void exit_program(t_ctrl *ctrl);
int key_hook(int keycode, t_ctrl *ctrl);
int close_window(t_ctrl *ctrl);

/* Declarations from utils.c */
int	check_extension(char *filename, char *ext);
void	free_char_array(char **array);
void	free_int_array(int *array);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
char **ft_split_strict(const char *s, char c);

/* Declarations from input.c */

/* Declarations from init.c */

/* Declarations from render.c */

/* Declarations from printing.c */
void	print_char_array(char **arr);
void	print_point(t_crd c);
void	print_map_struct(t_map *map);
void	print_coordinates(t_crd *crd, int count);

/* Declarations from main.c */
void connect_visible_neighbors(t_image image, t_map *map, int color);
int render_loop(t_ctrl *session);
t_ctrl init_session(void);
void	clear_screen(t_ctrl *session, int colour);
int main(int argc, char *argv[]);

/* Declarations from draw.c */
void draw_pixel(t_image image, t_crd point, int color);
void draw_line(t_image image, t_crd src, t_crd dest, int color);

/* Declarations from maffs.c */
int	derivative_of(int a, int b);
int	pos_or_neg(int a, int b);

/* Declarations from map_mgmt.c */
t_crd populate_coordinate(int x, int y, char *z);
char *read_full_map_as_str(char *file);
t_map *initialize_map();
void	free_map(t_map *map);
t_map *parse_map(char *filename);

/* Declarations from affine.c */
void	flatten3d_to_2d(t_crd point, double z_rotation);
void	scale(t_crd *point, int x_scalar, int y_scalar, int z_scalar);
void	translate(t_crd *point, int x_scalar, int y_scalar, int z_scalar);
void	flatten_isometrically(t_crd *point);

/* declarations end */



#endif // FDF_H
