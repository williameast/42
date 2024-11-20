/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:40:34 by weast             #+#    #+#             */
/*   Updated: 2024/09/27 14:13:33 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/push_swap.h"

t_node	*generate_node(int n)
{
    t_node	*new_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        return (NULL);
    new_node->n = n;
    return (new_node);
}

void	append_node(t_node **head, int n)
{
    t_node	*current_node;
    t_node	*new_node;

    new_node = generate_node(n);
    if (!new_node)
        return ;
    if (*head == NULL)
        *head = new_node;
    else
    {
        current_node = *head;
        while(current_node->next != NULL)
            current_node = current_node->next;
        current_node->next = new_node;
    }
}

int	list_len(t_node **head)
{
    t_node	*temp;
    int	i;

    temp = *head;
    i = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        i++;
    }
    return (i);
}

void	index_list(t_node **head)
{
    t_node *temp;
    int	i;

    i = 0;
    temp = *head;

    while (temp != NULL)
    {
        temp->index = i;
        temp = temp->next;
        i++;
    }
}

void	free_list(t_node *head)
{
    t_node	*temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
