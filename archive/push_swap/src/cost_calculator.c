/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_calculator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:00:03 by William           #+#    #+#             */
/*   Updated: 2024/11/12 14:40:19 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	get_move_cost(t_node **head)
{
    t_node	*temp;
    int	len;
    int	i;

    temp = *head;
    len = list_len(&temp);
    i = 1;
    if (len == 2)
    {
        temp->cost = 1;
        temp->next->cost = 2;
    }
    else
    {
        while (temp != NULL)
        {
            if  (i <= (len + 1) / 2)
                temp->cost = i;
            else
                temp->cost = -(len - i + 2);
            i++;
            temp = temp->next;
        }
    }
}


int	get_max_cost(t_node **head)
{
    t_node	*temp;
    int max;
    int	res;

    get_move_cost(head);
    temp = *head;
    max = temp->n;
    res = temp->cost;
    while (temp != NULL)
    {
        if (temp->n > max)
        {
            max = temp->n;
            res = temp->cost;
        }
        temp = temp->next;
    }
    return (res);
}

int	get_min_cost(t_node **head)
{
    t_node	*temp;
    int	min;
    int	res;

    get_move_cost(head);
    temp = *head;
    min = temp->n;
    res = temp->cost;
    while (temp != NULL)
    {
        if (temp->n < min)
        {
            min = temp->n;
            res = temp->cost;
        }
        temp = temp->next;
    }
    return (res);
}
