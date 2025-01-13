/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:05:43 by William           #+#    #+#             */
/*   Updated: 2025/01/12 14:53:02 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void	free_map(t_map *map)
{
	if (DEBUG)
	ft_printf("INFO: freeing map...\n");
	free(map->points);
	free(map);
	ft_printf("INFO: map has been freed.\n");
}

void	reset_session(t_ctrl *session)
{
	int	i;

	i = 0;
	while (i < session->map->points_len)
	{
		session->map->points[i].x = session->map->points[i].grid_x;
		session->map->points[i].y = session->map->points[i].grid_y;
		session->map->points[i].z = session->map->points[i].grid_z;
		i++;
	}
	session->offset = session->origin;
	session->draw_complete = 0;
	ft_printf("INFO: resetting to original state.\n");
}

