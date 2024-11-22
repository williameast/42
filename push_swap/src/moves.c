/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:32:12 by weast             #+#    #+#             */
/*   Updated: 2024/11/22 20:35:23 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


void	push_to_stack(t_stack *src, t_stack *dest, int print)
{
	t_node *obj;

	if (print)
		print_move("p", dest->name);
	if (src->top == NULL)
		return;
	obj = src->top;
	src->top = src->top->next;
	obj->next = dest->top;
	dest->top = obj;
}

void	rotate(t_stack *stack, int print)
{
	t_node *first;
	t_node *current;

	if (print)
		print_move("r", stack->name);
	if (stack->top == NULL || stack->top->next == NULL)
		return;
	first = stack->top;
	stack->top = first->next;
	current = stack->top;
	while(current->next != NULL)
		current = current->next;
	current->next = first;
	first->next = NULL;
}

void	reverse_rotate(t_stack *stack, int print)
{
	t_node *prev;
	t_node *current;

	if (print)
		print_move("rr", stack->name);
	if (stack->top == NULL || stack->top->next == NULL)
		return;
	prev = NULL;
	current = stack->top;
	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	prev->next = NULL;
	current->next = stack->top;
	stack->top = current;
}

void	swap(t_stack *stack, int print)
{
	t_node *first;
	t_node *second;

	if (print)
		print_move("s", stack->name);
	if (stack->top == NULL || stack->top->next == NULL)
		return;
	first = stack->top;
	second = stack->top->next;
	first->next = second->next;
	second->next = first;
	stack->top = second;
}
