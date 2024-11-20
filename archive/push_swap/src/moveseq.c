/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveseq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:51:04 by William           #+#    #+#             */
/*   Updated: 2024/10/02 11:45:08 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_moves *init_movseq(int initial_capacity)
{
	t_moves *seq = malloc(sizeof(t_moves));

	if (seq == NULL)
		return (NULL);
	seq->moves = malloc(initial_capacity * sizeof(int));
	if (seq->moves == NULL)
	{
		free(seq);
		return (NULL);
	}
	seq->size = 0;
	seq->capacity = initial_capacity;
	return (seq);
}

static int	resize_seq(t_moves *seq)
{
	int	new_capacity;
	int	*new_moves;
	int	i;

	new_capacity = seq->capacity * 2;
	new_moves = malloc(new_capacity * sizeof(int));
	if (new_moves == NULL)
	{
		printf("MOVSEQ: New move capacity allocation failed.\n");
		return (-1);
	}
	i = 0;
	while (i < seq->size)
	{
		new_moves[i] = seq->moves[i];
		i++;
	}
	free(seq->moves);
	seq->moves = new_moves;
	seq->capacity = new_capacity;
	return (0);
}

int	add_move(t_moves *seq, int move)
{
	if (seq->size == seq->capacity)
	{
		if (resize_seq(seq) != 0)
			return (-1);
	}
	seq->moves[seq->size++] = move;
	return (0);
}

void	free_movseq(t_moves *seq)
{
	free(seq->moves);
	free(seq);
}

/* ************************************************************************** */
/*                                                                            */
/*sa 0 |sb 1 |ss 2 |pa 3 |pb 4 |pp 5 |ra 6 |rb 7 |rr 8 |rra 9 |rrb 10 |rrr 11 */
/*                                                                            */
/* ************************************************************************** */
void	apply_movseq(t_node **a, t_node **b, t_moves *seq)
{
	if (!seq)
		return ;
	int	i;
	int move;
	i = 0;
	while (i < seq->size)
	{
		move = seq->moves[i];
		if (move == 0)
			swap(a);
		if (move == 1)
			swap(b);
		if (move == 2)
			swap_both(a, b);
		if (move == 3)
			push(b, a);
		if (move == 4)
			push(a, b);
		if (move == 5)
			push_both(a, b);
		if (move == 6)
			rotate(a);
		if (move == 7)
			rotate(b);
		if (move == 8)
			rotate_both(a, b);
		if (move == 9)
			reverse_rotate(a);
		if (move == 10)
			reverse_rotate(b);
		if (move == 11)
			reverse_rotate_both(a, b);
		i++;
	}
	free_movseq(seq);
}

void	apply_single_move(t_node **a, t_node **b, int move)
{
	if (move == 0)
		swap(a);
	if (move == 1)
		swap(b);
	if (move == 2)
		swap_both(a, b);
	if (move == 3)
		push(b, a);
	if (move == 4)
		push(a, b);
	if (move == 5)
		push_both(a, b);
	if (move == 6)
		rotate(a);
	if (move == 7)
		rotate(b);
	if (move == 8)
		rotate_both(a, b);
	if (move == 9)
		reverse_rotate(a);
	if (move == 10)
		reverse_rotate(b);
	if (move == 11)
		reverse_rotate_both(a, b);
}
