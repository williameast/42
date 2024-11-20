/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:14:39 by weast             #+#    #+#             */
/*   Updated: 2024/09/27 17:01:30 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	swap_both(t_node **a, t_node **b)
{
    swap(a);
    swap(b);
}

void	rotate_both(t_node **a, t_node **b)
{
    rotate(a);
    rotate(b);
}

void	reverse_rotate_both(t_node **a, t_node **b)
{
    reverse_rotate(a);
    reverse_rotate(b);
}

void	push_both(t_node **a, t_node **b)
{
    int	temp;
    if (*a == NULL && *b == NULL)
        return ;
    temp = (*a)->n;
    (*a)->n = (*b)->n;
    (*b)->n = temp;
}
