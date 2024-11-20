/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:28:49 by weast             #+#    #+#             */
/*   Updated: 2024/06/26 18:10:23 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	get_int_len(int n)
{
	int	i;

	i = !n;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

void	fill_number_str(char *res, unsigned int nb, int len)
{
	res[len] = '\0';
	while (len > 0)
	{
		res[--len] = nb % 10 + '0';
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	nb;
	int				len;
	int				is_neg;

	if (n >= 0)
	{
		nb = n;
		is_neg = 0;
	}
	else
	{
		nb = -n;
		is_neg = 1;
	}
	len = get_int_len(n) + is_neg;
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	fill_number_str(res, nb, len);
	if (is_neg)
		res[0] = '-';
	return (res);
}
/* #include <stdio.h> */
/* int main(void) { */
/*     printf("%s\n", ft_itoa(-123)); */
/*     printf("%s\n", ft_itoa(-1)); */
/*     printf("%s\n", ft_itoa(1)); */
/*     printf("%s\n", ft_itoa(123)); */
/*     printf("%s\n", ft_itoa(12334549)); */
/*     return 0; */
/* } */
