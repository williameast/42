/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:17:18 by weast             #+#    #+#             */
/*   Updated: 2024/04/23 18:38:53 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	obj;
	size_t			i;

	str = (unsigned char *) s;
	obj = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == obj)
			return ((void *) &str[i]);
		i++;
	}
	return (0);
}
