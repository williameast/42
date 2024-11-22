/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:03:53 by William           #+#    #+#             */
/*   Updated: 2024/11/22 20:36:13 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

// not sure this is being used?
void push(t_stack *stack, int value)
{
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
	t_node *current = stack->top;
    if (!new_node)
        return;
    new_node->n = value;
    new_node->next = NULL;
    if (stack->top == NULL)
        stack->top = new_node;
	else
	{
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

void	rotate_both(t_stack *a, t_stack *b)
{
	print_move("rr", 0);
	rotate(a, 0);
	rotate(b, 0);
}
void	reverse_rotate_both(t_stack *a, t_stack *b)
{
	print_move("rrr", 0);
	reverse_rotate(a, 0);
	reverse_rotate(b, 0);
}

/* void	push_both(t_stack *a, t_stack *b) */
/* { */
/* 	t_node	*top_a; */
/* 	t_node	*top_b; */
/* 	int		temp; */

/* 	print_move("pp", 0); */
/* 	if (a->top == NULL || b->top == NULL) */
/* 		return; */
/* 	top_a = a->top; */
/* 	top_b = b->top; */
/* 	temp = top_a->n; */
/* 	top_a->n = top_b->n; */
/* 	top_b->n = temp; */
/* } */
