/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:28:01 by William           #+#    #+#             */
/*   Updated: 2024/10/07 18:14:15 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*sa 0 |sb 1 |ss 2 |pa 3 |pb 4 |pp 5 |ra 6 |rb 7 |rr 8 |rra 9 |rrb 10 |rrr 11 */
/*                                                                            */
/* ************************************************************************** */
void	sort_triplets(int min_cost, int max_cost, t_moves *seq)
{
	if (max_cost == 1) // 3 2 1 or 3 1 2
	{
		if (min_cost == 2) // 3 1 2
		add_move(seq, 6); // ra
		else // 3 2 1
		{
			add_move(seq, 0);
			add_move(seq, 9);
		}
	}
	else if (max_cost != 1 && min_cost != 1) // 2 1 3 or 2 3 1
	{
		if (max_cost == -2) // 2 1 3
			add_move(seq, 0);
		else // 2 3 1
			add_move(seq, 9);
	}
	else // 1 3 2
	{
			add_move(seq, 6);
			add_move(seq, 0);
	}
}


/* ************************************************************************** */
/*                                                                            */
/*sa 0 |sb 1 |ss 2 |pa 3 |pb 4 |pp 5 |ra 6 |rb 7 |rr 8 |rra 9 |rrb 10 |rrr 11 */
/*                                                                            */
/* ************************************************************************** */

void	get_moves_to_extract_max(t_node **a, t_moves *seq)
{
	int max_cost;

	max_cost = get_max_cost(a);
	printf("attempting to move %i, current cost: %i\n", get_max(a), max_cost);
	if (max_cost > 1)
		while (max_cost != 2)
		{
			add_move(seq, 6);
			max_cost--;
		}
	else
		while (max_cost != -1)
		{
			if (max_cost == -1)
				max_cost = -max_cost;
			add_move(seq, 9);
			max_cost++;
		}
	add_move(seq, 4);
}

void	max_sort(t_node **a, t_moves *seq)
{
	int	len_a;

	len_a = list_len(a);
	while (len_a > 1)
	{
		get_move_cost(a);
		get_moves_to_extract_max(a, seq);
		len_a--;
	}
}

t_moves	*bin_sort(t_node **a, int segments)
{
	int	*bins;
	int bin_count;
	int	*arr;
	int	len;
	int	i;
	int	j;
	t_node *temp;
	t_node	*b;
	t_moves *seq;

	if (is_ascending(a))
		return (NULL);
	seq = init_movseq(50);
	i = 0;
	j = 0;
	temp = *a;
	b = NULL;
	len = list_len(a);
	arr = get_sorted_array_from_list(a);
	bins = get_segment_max_values(arr, segments, len, &bin_count);
	free(arr);

	while (j < bin_count)
	{
		while (i < len)
		{
			if (temp->n <= bins[j])
			{
				apply_single_move(a, &b, 4);
				add_move(seq, 4);
			}
			else
			{
				apply_single_move(a, &b, 6);
				add_move(seq, 6);
			}
			temp = temp->next;
		}
		j++;
		len  = list_len(&temp);
	}
	return (seq);
}
