/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:47 by weast             #+#    #+#             */
/*   Updated: 2025/01/07 18:46:08 by weast            ###   ########.fr       */
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
#define	CLAMP 0

// KEYS

#define KEY_W 119 // up
#define KEY_A 97  // left
#define KEY_S 115 // down
#define KEY_D 100 // right
#define KEY_R 114 // reset
#define KEY_I 105 // zoom In
#define KEY_O 111 // zoom Out
#define KEY_J 106 // rotate left
#define KEY_L 108 // rotate right
#define KEY_ESC 56307 // exit






// drawing objects:
// point contains both its absolute coords in the matrix read in as well as the
// points for rendering to the screen. grid_x and grid_y never change.
// visible is a switch that tells you if a point is to be plotted or not.
typedef struct s_crd {
	int	x;
	int	y;
    int	z;
	int grid_x;
	int grid_y;
	int	visible;
}			t_crd;

// a line object. consists of 2 points, the slope and a measure
// for determining the error term when plotting.
typedef struct s_line {
	t_crd	src;
	t_crd	dest;
	int		dx;
	int		dy;
	int		step_x;
	int		step_y;
	int		error;
	int		colour;
	int		visible;
}			t_line;


// rendering offset object. how much should each item be affected?
typedef struct s_offset {
	t_crd		value;
	int			scale;
	int			z_scale;
	double		u;
	double		v;
	int			state;
}			t_offset;

// map object. list of points, and metadata.
typedef struct s_map {
    t_crd	*points;
	int		points_len;
	int		rows;
	int		cols;
	int 	z_max;
	int 	z_min;
}			t_map;

// image, for drawing.
typedef struct s_image {
	void	*img_ptr;
	char 	*addr;
	int		bits_per_pixel;
	int 	line_length;
	int 	endian;
}			t_image;

// a session control instance. this is used to manage windows.
typedef struct s_ctrl {
	t_offset		offset;
	t_offset		origin;
	void			*mlx_ptr;
	void			*win_ptr;
	t_map			*map;
	t_image			image;
	int				draw_complete;
}			t_ctrl;



/* declarations */
/* Declarations from affine.c */
void	scale(t_crd *point, t_offset offset);
void	translate(t_crd *point, t_offset offset);
void	flatten_isometrically(t_crd *point);

/* Declarations from controls.c */
void exit_program(t_ctrl *session);
int key_hook(int keycode, t_ctrl *ctrl, t_offset offset);
int close_window(t_ctrl *ctrl);

/* Declarations from draw.c */
void draw_pixel(t_image image, t_crd point, int color);
void	draw_line(t_image image, t_crd src, t_crd dest, int colour);

/* Declarations from init.c */
t_crd	handle_out_of_bounds_line(t_crd point);
t_line	init_line(t_crd src, t_crd dest, int colour);
t_offset	init_offset(t_crd point, double u, double v);
t_ctrl set_state_to_origin(t_ctrl *session);
t_ctrl init_session(void);

/* Declarations from input.c */

/* Declarations from maffs.c */
int	derivative_of(int a, int b);
int	pos_or_neg(int a, int b);
int ternary(int a, int b, int c);
int	is_pixel_out_of_bounds(t_crd p);

/* Declarations from main.c */
void connect_visible_neighbors(t_image image, t_map *map, int color);
int render_loop(t_ctrl *session);
void	clear_screen(t_ctrl *session, int colour);
int main(int argc, char *argv[]);

/* Declarations from map_mgmt.c */
t_crd populate_coordinate(int x, int y, char *z);
char *read_full_map_as_str(char *file);
t_map *initialize_map();
void	free_map(t_map *map);
t_map *parse_map(char *filename);

/* Declarations from printing.c */
void	print_char_array(char **arr);
void	print_point(t_crd c);
void	print_map_struct(t_map *map);
void	print_coordinates(t_crd *crd, int count);

/* Declarations from render.c */

/* Declarations from utils.c */
int	check_extension(char *filename, char *ext);
void	free_char_array(char **array);
void	free_int_array(int *array);
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
char **ft_split_strict(const char *s, char c);
int inline_ternary(int	a, int b, int c);

/* declarations end */



#endif // FDF_H
