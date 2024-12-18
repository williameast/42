/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maffs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:34:41 by William           #+#    #+#             */
/*   Updated: 2024/12/18 13:35:17 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


int	derivative_of(int a, int b)
{
    return(abs(a - b));
}

int	pos_or_neg(int a, int b)
{
    if (a < b)
        return (1);
    return (-1);
}
