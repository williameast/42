/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:54:20 by William           #+#    #+#             */
/*   Updated: 2024/11/23 13:44:18 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	get_cost(t_stack *stack)
{
	t_node	*temp;
	int		i;
	int		len;

	len = stack_size(stack);
	temp = stack->top;
	i = 0;
	while (temp != NULL)
	{
		if (i <= len / 2)
			temp->cost = i;
		else
			temp->cost = -(len - i);
		i++;
		temp = temp->next;
	}
}

int	find_cheapest_candidate(t_stack *a)
{
	t_node	*temp;
	int		cheapest_cost;
	int		cheapest_candidate_cost;
	int		combined_cost;

	cheapest_cost = INT_MAX;
	cheapest_candidate_cost = 0;
	temp = a->top;
	while (temp != NULL)
	{
		combined_cost = ft_abs(temp->cost) + ft_abs(temp->target);
		if (combined_cost < cheapest_cost)
		{
			cheapest_cost = combined_cost;
			cheapest_candidate_cost = temp->cost;
		}
		temp = temp->next;
	}
	return (cheapest_candidate_cost);
}

int	find_cheapest_target(t_stack *a)
{
	t_node	*temp;
	int		cheapest_cost;
	int		cheapest_target;
	int		combined_cost;

	cheapest_cost = INT_MAX;
	cheapest_target = 0;
	temp = a->top;
	while (temp != NULL)
	{
		combined_cost = ft_abs(temp->cost) + ft_abs(temp->target);
		if (combined_cost < cheapest_cost)
		{
			cheapest_cost = combined_cost;
			cheapest_target = temp->target;
		}
		temp = temp->next;
	}
	return (cheapest_target);
}
