/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:32:12 by weast             #+#    #+#             */
/*   Updated: 2024/11/22 20:56:41 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	find_min(t_stack *stack)
{
	t_node	*temp;
	int	current_min;
	int	index;

	index_stack(stack);
	temp = stack->top;
	current_min = INT_MAX;
	while (temp != NULL)
	{
		if (current_min > temp->n)
		{
			current_min = temp->n;
			index = temp->index;
		}
		temp = temp->next;
	}
	return (index);
}

int	ft_abs(int nr)
{
	if (nr < 0)
		return (-nr);
	return (nr);
}

int	stack_size(t_stack *stack)
{
	int	size;
	t_node *current;

	current = stack->top;
	size = 0;

	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}
