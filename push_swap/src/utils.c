/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:54:20 by William           #+#    #+#             */
/*   Updated: 2024/11/22 20:29:10 by William          ###   ########.fr       */
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

/* int find_closest_position_ascending(t_stack *stack, int nr) */
/* { */
/*     t_node *temp = stack->top; */
/*     int target_index = 0; */
/*     int closest_larger_value = INT_MAX; */
/*     int closest_larger_index = -1; */

/*     while (temp != NULL) */
/*     { */
/*         // If the current node is larger than `nr` but smaller than any previously found larger value */
/*         if (temp->n > nr && temp->n < closest_larger_value) */
/*         { */
/*             closest_larger_value = temp->n; */
/*             closest_larger_index = target_index; */
/*         } */
/*         target_index++; */
/*         temp = temp->next; */
/*     } */

/*     // If a larger number was found, return its index (place `nr` before it). */
/*     if (closest_larger_index != -1) */
/*         return closest_larger_index; */

/*     // Otherwise, slot at the end of `A` (wrap around to the top). */
/*     return 0; */
/* } */

int find_closest_position_ascending2(t_stack *stack, int nr)
{
    t_node *temp = stack->top;
    int closest_larger_value = INT_MAX;
    int closest_larger_index = -1;
    int smallest_value = INT_MAX;
    int smallest_index = -1;
    int current_index = 0;

    while (temp != NULL)
    {
        if (temp->n < smallest_value)
        {
            smallest_value = temp->n;
            smallest_index = current_index;
        }
        if (temp->n > nr && temp->n < closest_larger_value)
        {
            closest_larger_value = temp->n;
            closest_larger_index = current_index;
        }
        current_index++;
        temp = temp->next;
    }
    if (closest_larger_index != -1)
        return closest_larger_index;
    return smallest_index;
}

int find_closest_position_ascending(t_stack *stack, int nr)
{
    t_node *temp = stack->top;
    int closest_larger_value = INT_MAX;
    int closest_larger_index = -1;
    int smallest_value = INT_MAX;
    int smallest_index = -1;
    int current_index = 0;
    int size = stack_size(stack);

    while (temp != NULL)
    {
        // Find the smallest value and its index
        if (temp->n < smallest_value)
        {
            smallest_value = temp->n;
            smallest_index = current_index;
        }

        // Find the closest larger value and its index
        if (temp->n > nr && temp->n < closest_larger_value)
        {
            closest_larger_value = temp->n;
            closest_larger_index = current_index;
        }

        current_index++;
        temp = temp->next;
    }

    int target_index;
    if (closest_larger_index != -1)
    {
        target_index = closest_larger_index;
    }
    else
    {
        target_index = smallest_index;
    }

    int rotate_distance = target_index;
    int reverse_rotate_distance = target_index - size;

    if (abs(rotate_distance) <= abs(reverse_rotate_distance))
    {
        return rotate_distance;
    }
    else
    {
        return reverse_rotate_distance;
    }
}


void	get_targets2(t_stack *a, t_stack *b)
{
	t_node *temp;

	temp = a->top;
	while (temp != NULL)
	{
		temp->target = find_closest_position(b, temp->n);
		temp = temp->next;
	}
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
/* int	find_cheapest_candidate(t_stack *a) */
/* { */
/* 	t_node *temp; */
/* 	int	current_cheapest; */
/* 	int cheapest; */
/* 	int cost; */

/* 	temp = a->top; */
/* 	cheapest = INT_MAX; */
/* 	while (temp != NULL) */
/* 	{ */
/* 		current_cheapest = ft_abs(temp->cost) + temp->target; */
/* 		if (cheapest > current_cheapest) */
/* 		{ */
/* 			cheapest = current_cheapest; */
/* 			cost = temp->cost; */
/* 		} */
/* 		temp = temp->next; */
/* 	} */
/* 	return (cost); */
/* } */

/* int	find_cheapest_target(t_stack *a) */
/* { */
/* 	t_node *temp; */
/* 	int	current_cheapest; */
/* 	int cheapest; */
/* 	int target; */

/* 	temp = a->top; */
/* 	cheapest = INT_MAX; */
/* 	while (temp != NULL) */
/* 	{ */
/* 		current_cheapest = ft_abs(temp->cost) + temp->target; */
/* 		if (cheapest > current_cheapest) */
/* 		{ */
/* 			cheapest = current_cheapest; */
/* 			target = temp->target; */
/* 		} */
/* 		temp = temp->next; */
/* 	} */
/* 	return (target); */
/* } */

int find_cheapest_candidate(t_stack *a)
{
    t_node *temp;
    int cheapest_cost = INT_MAX;
    int cheapest_candidate_cost = 0; // Default to 0 if stack is empty
    int combined_cost;

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
    return cheapest_candidate_cost;
}

int find_cheapest_target(t_stack *a)
{
    t_node *temp;
    int cheapest_cost = INT_MAX;
    int cheapest_target = 0; // Default to 0 if stack is empty
    int combined_cost;

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
    return cheapest_target;
}

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

void sort_triplets(t_stack *stack)
{
    int top;
	int mid;
	int bot;

    top = stack->top->n;
    mid = stack->top->next->n;
    bot = stack->top->next->next->n;
    if (top < mid && mid < bot)
        return;
    if (top > mid && top > bot)
    {
		rotate(stack, 1);
		if (stack->top->n > stack->top->next->n)
			swap(stack, 1);
    }
    else if (mid > top && mid > bot)
    {
		reverse_rotate(stack, 1);
		if (stack->top->n > stack->top->next->n)
			swap(stack, 1);
    }
    else if (bot > top && bot > mid)
		swap(stack, 1);
}




// this will index both stacks, and move all items until cutoff over to dest.

void	xdsort(t_stack *src, t_stack *dest, int cutoff)
{
	int	size;
	int cost_a;
	int cost_b;

	size = stack_size(src);
	while (size > cutoff)
	{
		cost_a = find_cheapest_candidate(src);
		cost_b = find_cheapest_target(src);
		rotate_n_times_combined(src, dest, cost_a, cost_b);
		push_to_stack(src, dest, 1);
		index_stack(dest);
		index_stack(src);
		get_targets(src, dest);
		get_cost(src);
		size--;
	}
}




void	slot_b_into_a(t_stack *a, t_stack *b)
{
	int	target_nr;

	while (b->top != NULL)
	{
		target_nr = b->top->target;

		while (target_nr > 0)
		{
			rotate(a, 1);
			target_nr--;
		}
		while (target_nr < 0)
		{
			reverse_rotate(a, 1);
			target_nr++;
		}
		push_to_stack(b, a, 1);
		get_targets_ascending(b, a);
	}
}


void	index_and_get_costs_of_stacks(t_stack *a, t_stack *b)
{
	index_stack(b);
	index_stack(a);
	get_targets(a, b);
	get_cost(a);
}

// assume a
void	willysort(t_stack *a, t_stack *b)
{
	if (stack_size(a) == 3)
		sort_triplets(a);
	else
	{
		push_to_stack(a, b, 1);
		push_to_stack(a, b, 1);
		index_and_get_costs_of_stacks(a, b);
		xdsort(a, b, 3);
		sort_triplets(a);
		get_targets_ascending(b, a);
		slot_b_into_a(a, b);
		get_cost(a);
		move_min_to_top(a);
	}

}

int	get_alignment_cost(int cost, int stack_size)
{
	if (cost > stack_size / 2)
		cost = cost - stack_size;
	return (cost);
}

int	get_absolute_cost(int cost_src, int cost_dest)
{
	int	total_cost;
	if ((cost_src > 0 && cost_dest > 0) || (cost_src < 0 && cost_dest < 0))
	{
		if (ft_abs(cost_src) > abs(cost_dest))
			total_cost = ft_abs(cost_src);
		else
			total_cost = ft_abs(cost_dest);
	}
	else
		total_cost = ft_abs(cost_src) + ft_abs(cost_dest);
	return (total_cost);
}

void	adv_cost_calculator(t_stack *src, t_stack *dest)
{
	t_node *temp;
	int	size_src;
	int	size_dest;
	int	cost_src;
	int	cost_dest;

	temp = src->top;
	size_src = stack_size(src);
	size_dest = stack_size(dest);
	get_targets(src, dest);
	while (temp != NULL)
	{
		cost_src = get_alignment_cost(temp->index, size_src);
		cost_dest = get_alignment_cost(temp->target, size_dest);
		temp->cost = get_absolute_cost(cost_src, cost_dest);
		temp= temp->next;
	}
}
