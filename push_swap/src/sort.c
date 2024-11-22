/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:55 by William           #+#    #+#             */
/*   Updated: 2024/11/22 22:45:05 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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

int	main(int argc, char *argv[])
{
    t_stack	*a;
    t_stack	*b;


    if (argc == 2)
        a = get_int_from_str(argv[1]);
    else
        a = get_int_from_argv(argc, argv);

    if (a == NULL || check_for_dup_in_stack(a))
    {
        ft_putstr_fd("Error\n", 2);
        return (0);
    }
	b = init_stack('b');
	willysort(a, b);
	/* check_output(a); */
    return 0;
}

