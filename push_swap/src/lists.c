/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:03:53 by William           #+#    #+#             */
/*   Updated: 2024/11/20 17:59:01 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


void	print_move(char *move, char stack)
{
	/* ft_putstr_fd(move, 0); */
	/* ft_putchar_fd(stack, 0); */
	/* ft_putchar_fd('\n', 0); */
	/* fflush(stdout); */
	if (stack == 0)
		printf("%s\n", move);
	else
		printf("%s%c\n", move, stack);
}

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
void	push_both(t_stack *a, t_stack *b)
{
	t_node	*top_a;
	t_node	*top_b;
	int		temp;

	print_move("pp", 0);
	if (a->top == NULL || b->top == NULL)
		return;
	top_a = a->top;
	top_b = b->top;
	temp = top_a->n;
	top_a->n = top_b->n;
	top_b->n = temp;
}
