/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:54:20 by William           #+#    #+#             */
/*   Updated: 2024/11/20 21:41:52 by William          ###   ########.fr       */
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

// you need to account for 5!
/* void sort_triplets(t_stack *stack) */
/* { */
/*     int top, mid, bot; */

/*     // Ensure the stack has exactly 3 elements */
/*     if (stack_size(stack) != 3) */
/*         return; */

/*     // Get the top, middle, and bottom elements */
/*     top = stack->top->n; */
/*     mid = stack->top->next->n; */
/*     bot = stack->top->next->next->n; */

/* 	if (top > mid && mid > bot) // correct */
/* 		return ; */

/* 	if (bot > mid && bot > top) */
/* 	{ */
/* 		if (bot > mid && mid > top) */
/* 			swap(stack, 1); */
/* 		reverse_rotate(stack, 1); */
/* 	} */
/* 	else if (bot < mid && bot > top) */
/* 	{ */
/* 		if (top < mid && mid > bot) */
/* 			swap(stack, 1); */
/* 		rotate(stack, 1); */
/* } */
/* } */
void sort_triplets(t_stack *stack)
{
    int top;
	int mid;
	int bot;

    top = stack->top->n;
    mid = stack->top->next->n;
    bot = stack->top->next->next->n;
    if (top > mid && mid > bot)
        return;
    if (top < mid && top < bot)
    {
		rotate(stack, 1);
		if (stack->top->n < stack->top->next->n)
			swap(stack, 1);
    }
    else if (mid < top && mid < bot)
    {
		reverse_rotate(stack, 1);
		if (stack->top->n < stack->top->next->n)
			swap(stack, 1);
    }
    else if (bot < top && bot < mid)
		swap(stack, 1);
}


int	find_insert_position(t_stack *stack, int value)
{
	t_node *temp = stack->top;
	int position = 0;


	// Traverse the stack to find the position where the value should be inserted
	while (temp && temp->next)
	{
		if (value > temp->n && value < temp->next->n)
			return position + 1;  // Found the correct position to insert

		position++;
		temp = temp->next;
	}

	// If we reach here, the value should go to the end of the stack
	return position + 1;

}

void	merge_stack_b_into_a(t_stack *a, t_stack *b)
{
	int insert_position;

	// While stack B is not empty, move elements from B to A
	while (b->top != NULL)
	{
		// Get the top element from stack B
		int value = b->top->n;

		// Find the insert position for the value in stack A
		insert_position = find_insert_position(a, value);

		// Rotate or reverse rotate stack A to reach the correct position
		if (insert_position == 0)
		{
			// Rotate A until the value should be at the top
			while (a->top->n < value)
				rotate(a, 1);
		}
		else if (insert_position == stack_size(a))
		{
			// Rotate A until the value should be at the end
			while (a->top->n > value)
				reverse_rotate(a, 1);
		}
		else
		{
			// Handle insertion at any other position (between 0 and stack size)
			while (a->top->n < value)
				rotate(a, 1);
		}

		// Push the element from B to A after positioning
		push_to_stack(b, a, 1);
	}
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
		print_both(src, dest);
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
		printf("%s\n", "SORTING TRIPS");
		sort_triplets(a);
		merge_stack_b_into_a(a, b);
		print_both(a, b);
	}
}

/* void	funnysort(t_stack *a, t_stack *b) */
/* { */
/* 	int	size; */
/* 	int cost_a; */
/* 	int cost_b; */

/* 	size = stack_size(a); */
/* 	while (size > 3) */
/* 	{ */
/* 		cost_a = find_cheapest_candidate(a); */
/* 		cost_b = find_cheapest_target(a); */
/* 		rotate_n_times_combined(a, b, cost_a, cost_b); */
/* 		push_to_stack(a, b, 1); */
/* 		index_stack(b); */
/* 		index_stack(a); */
/* 		get_targets(a, b); */
/* 		get_cost(a); */
/* 		size--; */
/* 	} */

/* 	sort_triplets(a); */
/* 	move_max_to_top(b); */
/* 	size = stack_size(b); */
/* 	while(size > 0) */
/* 	{ */
/* 		push_to_stack(b, a, 1); */
/* 		size--; */
/* 	} */
/* } */






/* void	funnysort(t_stack *a, t_stack *b) */
/* { */
/* 	int	size; */
/* 	int target; */
/* 	int candidate; */

/* 	size = stack_size(a); */
/* 	while(size > 0) */
/* 	{ */
/* 		candidate = find_cheapest_candidate(a); */
/* 		target = find_cheapest_target(a); */
/* 		rotate_n_times(a, candidate); */
/* 		rotate_n_times(b, target); */
/* 		push_to_stack(a, b, 1); */
/* 		index_stack(b); */
/* 		index_stack(a); */
/* 		get_targets(a, b); */
/* 		get_cost(a); */
/* 		size--; */
/* 	} */
/* 	move_max_to_top(b); */
/* 	size = stack_size(b); */
/* 	while(size > 0) */
/* 	{ */
/* 		push_to_stack(b, a, 1); */
/* 		size--; */
/* 	} */
/* } */
