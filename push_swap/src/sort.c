/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:55 by William           #+#    #+#             */
/*   Updated: 2025/01/07 15:27:50 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_triplets(t_stack *stack)
{
	int	top;
	int	mid;
	int	bot;

	top = stack->top->n;
	mid = stack->top->next->n;
	bot = stack->top->next->next->n;
	if (top < mid && mid < bot)
		return ;
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

void	xdsort(t_stack *src, t_stack *dest, int cutoff)
{
	int	size;
	int	cost_a;
	int	cost_b;

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

void	sort_less_than_three(t_stack *stack)
{
	int	size;

	size = stack_size(stack);
	if (size <= 1 || stack->top->n < stack->top->next->n)
		return ;
	else
		swap(stack, 1);
}

void	willysort(t_stack *a, t_stack *b)
{
	int	size;

	if (is_sorted(a))
		return ;
	size = stack_size(a);
	if (size < 3)
		sort_less_than_three(a);
	else if (size == 3)
		sort_triplets(a);
	else
	{
		if (size > 4)
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
	{
		if (argv[1][0] == '\0')
			return (0);
		a = get_int_from_str(argv[1]);
	}
	else
		a = get_int_from_argv(argc, argv);
	if (a == NULL || check_for_dup_in_stack(a))
	{
		ft_putstr_fd("Error\n", 2);
		free_stack(a);
		return (0);
	}
	b = init_stack('b');
	willysort(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
