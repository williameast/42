/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:54:20 by William           #+#    #+#             */
/*   Updated: 2024/11/22 22:30:11 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int find_closest_smaller(t_stack *stack, int nr, int *closest_smaller_value)
{
    t_node *temp = stack->top;
    int closest_smaller_index = -1;

    while (temp != NULL)
    {
        if (temp->n < nr && temp->n > *closest_smaller_value)
        {
            *closest_smaller_value = temp->n;
            closest_smaller_index = temp->index;
        }
        temp = temp->next;
    }
    return closest_smaller_index;
}

int find_closest_larger(t_stack *stack, int nr, int *closest_larger_value)
{
    t_node *temp = stack->top;
    int closest_larger_index = -1;

    while (temp != NULL)
    {
        if (temp->n > nr && temp->n < *closest_larger_value)
        {
            *closest_larger_value = temp->n;
            closest_larger_index = temp->index;
        }
        temp = temp->next;
    }
    return closest_larger_index;
}

int find_closest_position(t_stack *stack, int nr)
{
    int closest_smaller_value;
    int closest_larger_value;
    int closest_smaller_index;
    int closest_larger_index;

    closest_smaller_value = INT_MIN;
    closest_larger_value = INT_MAX;
    closest_smaller_index = find_closest_smaller(stack, nr, &closest_smaller_value);
    closest_larger_index = find_closest_larger(stack, nr, &closest_larger_value);
    if (closest_smaller_index != -1)
        return closest_smaller_index;
    else
        return closest_larger_index + 1;
}

void	get_targets(t_stack *a, t_stack *b)
{
	t_node *temp;
	int	target;
	int	size;

	temp = a->top;
	size = stack_size(b);

	while (temp != NULL)
	{
		target = find_closest_position(b, temp->n);

		if (target > size / 2)
			target = target - size;

		temp->target = target;
		temp = temp->next;
	}
}


void	get_targets_ascending(t_stack *a, t_stack *b)
{
	t_node *temp;

	temp = a->top;
	while (temp != NULL)
	{
		temp->target = find_closest_position_ascending(b, temp->n);
		temp = temp->next;
	}
}