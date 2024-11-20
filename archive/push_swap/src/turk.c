/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:19:27 by William           #+#    #+#             */
/*   Updated: 2024/11/12 15:42:10 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


/*
 * assuming that: list is longer than 3
 * id not already sorted!
 * then:
 *
 * move over two items
 *
 * */

/* ************************************************************************** */
/*                                                                            */
/*sa 0 |sb 1 |ss 2 |pa 3 |pb 4 |pp 5 |ra 6 |rb 7 |rr 8 |rra 9 |rrb 10 |rrr 11 */
/*                                                                            */
/* ************************************************************************** */

/* t_moves	*turk_sort(t_node **a) */
/* { */
/* 	t_moves	*seq; */

/* 	seq = init_movseq(50); */
/* 	add_move(seq, 4); */
/* 	add_move(seq, 4); */
/* 	return (seq); */
/* } */


int	get_last(t_node **stack)
{
	t_node	*temp;

	temp = *stack;

	while (temp != NULL)
	{
		temp = temp->next;
	}
	return (temp->n);
}


int get_max_bits(t_node **stack)
{
	int	max_val;
	int	bits;
	t_node *temp;

	temp = *stack;
	bits = 0;
	max_val = 0;

	while (temp != NULL)
	{
		if (temp->n > max_val)
			max_val = temp->n;
		temp = temp->next;
	}
	while ((max_val >> bits) != 0)
		bits++;
	return bits;
}

void	bit_sort(t_node **stackA, t_node **stackB)
{
	int	max_bits;
	int	bit;
	int	size;
	int	i;
	int	head;



	max_bits = get_max_bits(stackA);
	bit = 0;
	i = 0;

	while (bit < max_bits)
	{
		size = list_len(stackA);
		while (i < size)
		{
			head = (*stackA)->n;
			if ((head >> bit) & 1)
				rotate(stackA);
			else
				push(stackA, stackB);
		}
	bit++;

	}

	}


}


void	prep_stack_b(t_node **stackA, t_node **stackB)
{
	push(stackA, stackB);
	push(stackA, stackB);
	if((*stackB)->n < (*stackB)->next->n)
		swap(stackB);
	get_move_cost(stackB);
	get_move_cost(stackA);
}


























/* returns the cost to slot a nr between its correct neighbours */
int	cost_to_move_bw_neighbours(t_node **stack, int nr)
{
	t_node	*temp;
	temp = *stack;
	int	count;

	count = 0;
	/* if ((nr > temp->n && nr > get_last(stack)) || (nr < temp->n && get_last(stack))) */
	/* 	return (1); */

	while (temp != NULL)
	{
		if (temp->n > nr && temp->next->n < nr)
		{
			return (count);
		}
		temp = temp->next;
		count++;
	}
	return (count);
}
