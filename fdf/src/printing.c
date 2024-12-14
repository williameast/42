/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2024/12/14 01:24:31 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void	print_point(t_crd c)
{
	ft_printf("x=%i, y=%i, z=%i, visible=%i\n", c.x, c.y, c.z, c.visible);
}

void	print_map_struct(t_map *map)
{
	int len;
	int	i;
	t_crd t;

	if (!map)
	{
		ft_printf("ERROR: map object not found, nothing to print.\n");
		return ;
	}
	len = map->rows * map->cols;
	i = 0;
	ft_printf("rows: %i, cols: %i\n", map->rows, map->cols);

	while (i < len)
	{
		t = map->points[i];
		ft_printf("%i: x= %i, y= %i, z= %i, vis= %i\n", i, t.x, t.y, t.z, t.visible);
		i++;
	}
}

void	print_coordinates(t_crd *crd, int count)
{
	int	i;

	i = 0;
	if (!crd)
	{
		ft_printf("ERROR: map object not found, nothing to print.\n");
		return ;
	}

	while (i < count)
	{
		ft_printf("[%i]: ", i);
		print_point(crd[i]);
		i++;
	}
}

void print_map(t_map *map)
{
    int i;
    int j;
	int k;

    i = 0;
	k = 0;
	if (!map)
		return ;
	while (k++ < map->cols)
		ft_printf("__");
	ft_printf("\n");
    while (i < map->rows)
    {
        j = 0;
        while (j < map->cols)
        {
			if (map->points[i * map->cols + j].visible)
				ft_printf("%i ", map->points[i * map->cols + j].z);
            j++;
        }
        ft_printf("\n");
        i++;
    }
}
