/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:47:11 by weast             #+#    #+#             */
/*   Updated: 2024/11/12 14:49:05 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	swap(t_node **stack)
{
    int	temp;

    if ((*stack) == NULL || (*stack)->next == NULL)
        return ;
    temp = (*stack)->n;
    (*stack)->n = (*stack)->next->n;
    (*stack)->next->n = temp;
    (*stack)->cost = (*stack)->next->cost;
    (*stack)->next->cost = temp;
}

void	rotate(t_node **stack)
{
    t_node *first;
    t_node *second;
    t_node *last;

    if (*stack == NULL || (*stack)->next == NULL)
        return ;
    first = *stack;
    second = first->next;
    last = first;
    while (last->next != NULL)
        last = last->next;
    last->next = first;
    first->next = NULL;
    *stack = second;
}

void	reverse_rotate(t_node **stack)
{
    t_node *second_last;
    t_node *last;

    if (*stack == NULL || (*stack)->next == NULL)
        return ;
    second_last = NULL;
    last = *stack;
    while (last->next != NULL)
    {
        second_last = last;
        last = last->next;
    }
    last->next = *stack;
    second_last->next = NULL;
    *stack = last;
}

void	push(t_node **src_stack, t_node **dest_stack)
{
    t_node *first;

    if (*src_stack == NULL)
        return ;
    first = *src_stack;
    *src_stack = first->next;
    first->next = *dest_stack;
    *dest_stack = first;
}
