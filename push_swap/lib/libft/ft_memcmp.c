/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:42:32 by weast             #+#    #+#             */
/*   Updated: 2024/04/23 18:57:39 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/* #include <stdio.h> */
/* #include <string.h> */
/* int main() { */
/* 	char str1[] = "Hello, World!"; */
/* 	char str2[] = "Hello, OpenAI!"; */

/* 	int result = ft_memcmp(str1, str2, 10); */

/* 	if (result == 0) { */
/* 		printf("The strings are equal.\n"); */
/* 	} else if (result < 0) { */
/* 		printf("The first string is less than the second string.\n"); */
/* 	} else { */
/* 		printf("The first string is greater than the second string.\n"); */
/* 	} */
/* 	return 0; */
/* } */
