/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:32:12 by weast             #+#    #+#             */
/*   Updated: 2024/11/26 12:39:00 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	print_move(char *move, char stack)
{
	if (stack == 0)
		ft_putstr_fd(move, 1);
	else
	{
		ft_putstr_fd(move, 1);
		ft_putchar_fd(stack, 1);
	}
	ft_putchar_fd('\n', 1);
}
