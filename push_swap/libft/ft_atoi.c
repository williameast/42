/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:30:26 by weast             #+#    #+#             */
/*   Updated: 2024/09/23 16:42:58 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
/* int	ft_atoi(char *str) */
/* { */
/* 	int	i; */
/* 	int	res; */
/* 	int	sign; */

/* 	i = 0; */
/* 	res = 0; */
/* 	sign = 1; */
/* 	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13)) */
/* 		i++; */
/* 	while (str[i] == '-' || str[i] == '+') */
/* 	{ */
/* 		if (str[i] == '-') */
/* 			sign *= -1; */
/* 		i++; */
/* 	} */
/* 	while ('0' <= str[i] && str[i] <= '9') */
/* 	{ */
/* 		res *= 10; */
/* 		res += str[i] - '0'; */
/* 		i++; */
/* 	} */
/* 	return (res * sign); */
/* } */

int	check_overflow(long res, int sign)
{
	if (sign == 1 && res > INT_MAX)
		return 0;
	else if (sign == -1 && -res < INT_MIN)
		return 0;
	else
		return 1;
}

int	ft_atoi(const char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (!check_overflow(res, sign))
			return (0);
	}
	return ((int)(res * sign));
}
