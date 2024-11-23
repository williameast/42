/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:50:25 by weast             #+#    #+#             */
/*   Updated: 2024/04/23 18:55:49 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *) b;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
/* #include <stdio.h> */
/* int main() { */
/*     char str[20]; */
/*     size_t len = 15; */
/*     int value = 'A'; // ASCII value of 'A' */

/*     // Call your memset implementation */
/*     ft_memset(str, value, len); */

/*     // Print the result */
/*     printf("Memory after memset: %s\n", str); */

/*     return 0; */
/* } */
