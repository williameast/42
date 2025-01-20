/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:47 by weast             #+#    #+#             */
/*   Updated: 2025/01/19 19:38:59 by William          ###   ########.fr       */
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
# include <limits.h>
# include <mlx.h>
# include <math.h>


#define	WIN_WIDTH 1000
#define 	WIN_HEIGHT 1000
#define 	TITLE "Wire mesh render"

#define	GREEN  0x00FF00
#define	RED  0xFF0000
#define	BLUE  0x0000FF

#define Z_SCALE 1.5
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
#define KEY_K 107 // rotate right
#define KEY_SPC 32 // cycle cabinet
#define KEY_ESC 65307 // exit


// DEBUG SWITCHES
#define RENDER 1 // 0 to supress mlx generation. for testing parser
#define DEBUG 0 // print info when pixels are ignored or dropped.

// drawing objects:
// point contains both its absolute coords in the matrix read in as well as the
// points for rendering to the screen. grid_x and grid_y never change.
// visible is a switch that tells you if a point is to be plotted or not.

typedef struct s_primitive {
	int	a;
	int	b;
    int	c;
}			t_primitive;

typedef struct s_crd {
	int	x;
	int	y;
    int	z;
	int grid_x;
	int grid_y;
	int grid_z;
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
	int		visible;
	float	z_increment;
	float	current_z;
}			t_line;


// rendering offset object. how much should each item be affected?
typedef struct s_offset {
	int			x_offset;
	int			y_offset;
	int			scale;
	double			z_scale;
	double		rotation;
	int		rotation_changed;
	int			state;
}			t_offset;

// map object. list of points, and metadata.
typedef struct s_map {
    t_crd	*points;
	int		points_len;
	int		rows;
	int		cols;
	int 	x_max;
	int 	x_min;
	int 	y_min;
	int 	y_max;
	int 	z_min;
	int 	z_max;
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
	int				is_isometric;
	int				centered;
}			t_ctrl;



/* declarations */
/* Declarations from controls.c */
void	exit_program(t_ctrl *session);
int	close_window(t_ctrl *ctrl);
int	key_hook(int keycode, t_ctrl *ctrl);

/* Declarations from parsing.c */
char **read_and_split_map(char *filename);
t_map *parse_map(char *filename);

/* Declarations from utils.c */
int	check_extension(char *filename, char *ext);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/* Declarations from cleanup.c */
void	free_char_array(char **array);
void	free_int_array(int *array);
void	free_map(t_map *map);
void	reset_session(t_ctrl *session);

/* Declarations from init.c */
t_crd	handle_out_of_bounds_line(t_crd point);
t_line	init_line(t_crd src, t_crd dest);
t_map	*init_map(void);
void	init_offset(t_ctrl *session, int x, int y, double z_scalar);
t_ctrl	init_session(t_map *map);

/* Declarations from render.c */
void	center_image(t_ctrl *se);
int	render_loop(t_ctrl *session);

/* Declarations from colours.c */
int	get_colour(float z, int z_min, int z_max);

/* Declarations from printing.c */
void	print_char_array(char **arr);
void	print_point(t_crd c);
void	print_map_struct(t_map *map);
void	print_coordinates(t_crd *crd, int count);

/* Declarations from main.c */
void	apply_offset(t_ctrl *sesh);
int	main(int argc, char *argv[]);

/* Declarations from draw.c */
void	draw_line(t_image image, t_crd src, t_crd dest, t_primitive z);
void	clear_image(t_ctrl *session, int width, int height);

/* Declarations from maffs.c */
int	ternary(int a, int b, int c);
int	is_pixel_out_of_bounds(t_crd p);
void	get_coordinate_limits(t_map *map);
float	get_z_scale_factor(t_map *map);

/* Declarations from map_mgmt.c */
t_crd populate_coordinate(int x, int y, char *z);
t_crd *parse_row_to_coordinates(char *row, int y, int *count);
int append_row_to_map(t_map *map, t_crd *row_coords, int row_length);

/* Declarations from affine.c */
void	translate(t_ctrl *session, int dx, int dy);
void	scale(t_ctrl *session, int factor);
void	flatten_isometrically(t_crd *point);
void	flatten_cabinet(t_crd *point);

/* declarations end */



#endif // FDF_H
