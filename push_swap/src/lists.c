/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:03:53 by William           #+#    #+#             */
/*   Updated: 2024/11/15 13:29:47 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


void	print_move(char *move, char stack)
{
	/* ft_putstr_fd(move, 0); */
	/* ft_putchar_fd(stack, 0); */
	/* ft_putchar_fd('\n', 0); */
	/* fflush(stdout); */
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

void	push_to_stack(t_stack *src, t_stack *dest)
{
	t_node *obj;

	print_move("p", dest->name);
	if (src->top == NULL)
		return;
	obj = src->top;
	src->top = src->top->next;
	obj->next = dest->top;
	dest->top = obj;
}

void	rotate(t_stack *stack)
{
	t_node *first;
	t_node *current;

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

void	reverse_rotate(t_stack *stack)
{
	t_node *prev;
	t_node *current;

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

/* void print_stack(t_stack *stack) { */
/*     t_node *current = stack->top; */
/*     while (current) { */
/*         printf("%d ", current->n); */
/*         current = current->next; */
/*     } */
/*     printf("\n"); */
/* } */
