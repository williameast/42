/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2024/12/13 14:13:47 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void	print_point(t_crd c)
{
	printf("x=%i, y=%i, z=%i, visible=%i\n", c.x, c.y, c.z, c.visible);
}

void	print_coordinates(t_crd *crd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_printf("[%i]: ", i);
		print_point(crd[i]);
		i++;
	}
}
