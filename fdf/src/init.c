/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2024/12/12 15:03:45 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_map *init_map(void)
{
	t_map	*map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_printf("ERROR: map memory allocation failed.\n");
		return (NULL);
	}
	map->points = NULL;
	map->rows = 0;
	map->cols = 0;
	ft_printf("INFO: map initisalized.\n");
	return (map);
}
