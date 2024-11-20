/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:47:37 by weast             #+#    #+#             */
/*   Updated: 2024/08/08 14:56:26 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/* size_t	ft_strlcat(char *dest, const char *source, size_t n) */
/* { */
/* 	size_t	i; */
/* 	size_t	j; */
/* 	size_t	dest_len; */
/* 	size_t	source_len; */

/* 	dest_len = ft_strlen(dest); */
/* 	source_len = ft_strlen(source); */
/* 	i = 0; */
/* 	j = source_len + 1; */
/* 	if (dest_len < (n - 1) && n > 0) */
/* 	{ */
/* 		while (source[i] && dest_len + i < n - 1) */
/* 		{ */
/* 			dest[j] = source[i]; */
/* 			i++; */
/* 			j++; */
/* 		} */
/* 		dest[j] = '\0'; */
/* 	} */
/* 	if (dest_len >= n) */
/* 		dest_len = n; */
/* 	return (dest_len + source_len); */
/* } */

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j] && j < size)
		j++;
	while (src[k] && ((j + k + 1) < size))
	{
		dest[j + k] = src[k];
		k++;
	}
	if (j != size)
		dest[j + k] = '\0';
	return (j + k);
}
