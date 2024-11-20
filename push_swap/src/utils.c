/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:54:20 by William           #+#    #+#             */
/*   Updated: 2024/11/14 14:42:22 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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

int	get_max_bits(t_stack *stack)
{
	int	max_value;
	int bits;
	t_node	*current;

	current = stack->top;
	bits = 0;
	while (current != NULL)
	{
		if (current->n > max_value)
			max_value = current->n;
		current = current->next;
	}
	while ((max_value >> bits) != 0)
		bits++;
	return (bits);
}

void	index_stack(t_stack *stack)
{
	t_node *current;
	int	index;

	index = 0;
	current = stack->top;
	while (current != NULL)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}

int	find_closest_smaller_nr(t_stack *stack, int nr)
{
	t_node	*temp;
	int	index;

	temp = stack->top;
	index = 0;
	while (temp != NULL)
	{
		if (nr > temp->n)
			index = temp->index;
		temp = temp->next;
	}
	return (index);
}


int find_closest_position(t_stack *stack, int nr)
{
    t_node *temp = stack->top;
    int closest_smaller_index = -1;
    int closest_larger_index = -1;
    int closest_smaller_value = INT_MIN;
    int closest_larger_value = INT_MAX;

    while (temp != NULL)
    {
        if (temp->n < nr && temp->n > closest_smaller_value)
        {
            closest_smaller_value = temp->n;
            closest_smaller_index = temp->index;
        }
        else if (temp->n > nr && temp->n < closest_larger_value)
        {
            closest_larger_value = temp->n;
            closest_larger_index = temp->index;
        }
        temp = temp->next;
    }
    if (closest_smaller_index != -1)
        return closest_smaller_index;
    else
        return closest_larger_index + 1;
}

void	get_targets(t_stack *a, t_stack *b)
{
	t_node *temp;

	temp = a->top;
	while (temp != NULL)
	{
		temp->target = find_closest_position(b, temp->n);
		temp = temp->next;
	}
}

void	get_cost(t_stack *stack)
{
	t_node	*temp;
	int	i;
	int	len;

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


int	ft_abs(int nr)
{
	if (nr < 0)
		return (-nr);
	return (nr);
}

// returns the cost of the cheapest candiate. the sign tells u if u need to reverse rotate or rotate.
int	find_cheapest_candidate(t_stack *a)
{
	t_node *temp;
	int	current_cheapest;
	int cheapest;
	int cost;

	temp = a->top;
	cheapest = INT_MAX;
	while (temp != NULL)
	{
		current_cheapest = ft_abs(temp->cost) + temp->target;
		if (cheapest > current_cheapest)
		{
			cheapest = current_cheapest;
			cost = temp->cost;
		}
		temp = temp->next;
	}
	return (cost);
}

int	find_cheapest_target(t_stack *a)
{
	t_node *temp;
	int	current_cheapest;
	int cheapest;
	int target;

	temp = a->top;
	cheapest = INT_MAX;
	while (temp != NULL)
	{
		current_cheapest = ft_abs(temp->cost) + temp->target;
		if (cheapest > current_cheapest)
		{
			cheapest = current_cheapest;
			target = temp->target;
		}
		temp = temp->next;
	}
	return (target);
}

void	rotate_n_times(t_stack *stack, int cost)
{
	if (cost < 0)
	{
		while(cost < 0)
		{
			reverse_rotate(stack);
			cost++;
		}
	}
	else
		while(cost > 0)
		{
			rotate(stack);
			cost--;
		}
}


int	find_max(t_stack *stack)
{
	t_node	*temp;
	int	current_max;
	int	index;

	index_stack(stack);
	temp = stack->top;
	current_max = INT_MIN;
	while (temp != NULL)
	{
		if (current_max < temp->n)
		{
			current_max = temp->n;
			index = temp->index;
		}
		temp = temp->next;
	}
	return (index);
}


void	move_max_to_top(t_stack *stack)
{
	int	max_index;
	int	cost;
	t_node *temp;

	max_index = find_max(stack);
	temp = stack->top;
	get_cost(stack);
	while (1)
	{
		if (max_index == temp->index)
		{
			cost = temp->cost;
			break;
		}
		temp = temp->next;
	}
	rotate_n_times(stack, cost);
}


void	funnysort(t_stack *a, t_stack *b)
{
	int	size;
	int target;
	int candidate;

	size = stack_size(a);
	while(size > 0)
	{
		/* print_both(a, b); */
		candidate = find_cheapest_candidate(a);
		target = find_cheapest_target(a);
		rotate_n_times(a, candidate);
		rotate_n_times(b, target);
		push_to_stack(a, b);
		index_stack(b);
		index_stack(a);
		get_targets(a, b);
		get_cost(a);
		size--;
	}
	move_max_to_top(b);
	size = stack_size(b);
	while(size > 0)
	{
		push_to_stack(b, a);
		size--;
	}
}
