/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:36:04 by William           #+#    #+#             */
/*   Updated: 2024/11/12 18:45:22 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


int	find_closest_smaller_nr(t_node **stack, int nr)
{
	t_node	*temp;
	int	index;

	temp = *stack;
	index = 0;

	while (temp != NULL)
	{
		if (nr > temp->n)
		{
			index = temp->index;
		}
		temp = temp->next;
	}
	return (index);
}
