/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maffs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:34:41 by William           #+#    #+#             */
/*   Updated: 2025/01/07 15:17:47 by weast            ###   ########.fr       */
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

int ternary(int a, int b, int c)
{
    if (a)
        return (b);
    else
        return (c);
}

int	is_pixel_out_of_bounds(t_crd p)
{
    return (p.x < 0 || p.y < 0 ||
        p.x >= WIN_WIDTH || p.y >= WIN_HEIGHT);
}
