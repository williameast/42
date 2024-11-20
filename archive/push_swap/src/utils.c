/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:08:50 by William           #+#    #+#             */
/*   Updated: 2024/09/27 21:13:50 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/push_swap.h"

int	is_ascending(t_node **head)
{
    t_node	*temp;

    temp = *head;
    while (temp->next != NULL)
    {
        if (temp->n > temp->next->n)
            return (0);
        temp = temp->next;
    }
    return (1);
}

int	is_decending(t_node **head)
{
    t_node	*temp;

    temp = *head;
    while (temp->next != NULL)
    {
        if (temp->n < temp->next->n)
            return (0);
        temp = temp->next;
    }
    return (1);
}

int	get_max(t_node **head)
{
    t_node	*temp;
    int max;

    temp = *head;
    max = temp->n;
    while (temp != NULL)
    {
        if (temp->n > max)
            max = temp->n;
        temp = temp->next;
    }
    return (max);
}

int	get_min(t_node **head)
{
    t_node	*temp;
    int min;

    temp = *head;
    min = temp->n;
    while (temp != NULL)
    {
        if (temp->n < min)
            min = temp->n;
        temp = temp->next;
    }
    return (min);
}

int	ft_abs(int n)
{
    if (n < 0)
        return (-n);
    else
        return (n);
}
