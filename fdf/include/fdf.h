/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:56:47 by weast             #+#    #+#             */
/*   Updated: 2024/11/26 17:25:14 by weast            ###   ########.fr       */
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
#include <stdio.h>
#include <fcntl.h>
#include <mlx.h>
#include <math.h>


/* stuctures */
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

/* declarations */

/* Declarations from test.c */
int read_something(void);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	main(void);

/* Declarations from read_file.c */

/* declarations end */



#endif // FDF_H
