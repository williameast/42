/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:04:55 by weast             #+#    #+#             */
/*   Updated: 2024/04/19 13:40:01 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dest, const char *source, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize > 0)
	{
		while (source[i] != '\0' && i < (destsize - 1))
		{
			dest[i] = source[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (source[i] != '\0')
		i++;
	return (i);
}
