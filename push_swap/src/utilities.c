/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:32:12 by weast             #+#    #+#             */
/*   Updated: 2024/11/22 20:52:57 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	rotate_n_times(t_stack *stack, int cost)
{
	while(cost < 0)
	{
		reverse_rotate(stack, 1);
		cost++;
	}
	while(cost > 0)
	{
		rotate(stack, 1);
		cost--;
	}
}

void	rotate_n_times_combined(t_stack *a, t_stack *b, int cost_a, int cost_b)
{
	while (cost_a > 0 && cost_b > 0)
	{
		rotate_both(a, b);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		reverse_rotate_both(a, b);
		cost_a++;
		cost_b++;
	}
	rotate_n_times(a, cost_a);
	rotate_n_times(b, cost_b);
}

void	move_min_to_top(t_stack *stack)
{
	int	min_index;
	int	cost;
	t_node *temp;

	min_index = find_min(stack);
	temp = stack->top;
	get_cost(stack);
	while (1)
	{
		if (min_index == temp->index)
		{
			cost = temp->cost;
			break;
		}
		temp = temp->next;
	}
	rotate_n_times(stack, cost);
}

void	index_and_get_costs_of_stacks(t_stack *a, t_stack *b)
{
	index_stack(b);
	index_stack(a);
	get_targets(a, b);
	get_cost(a);
}