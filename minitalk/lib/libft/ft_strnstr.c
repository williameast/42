/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:35:00 by weast             #+#    #+#             */
/*   Updated: 2024/06/30 18:05:45 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

/* char	*ft_strnstr(const char *str, const char *pattern, size_t len) */
/* { */
/* 	size_t	i; */
/* 	size_t	j; */

/* 	i = 0; */
/* 	if (*pattern == '\0' || str == NULL) */
/* 		return ((char *)str); */
/* 	while (str[i] != '\0' && i < len) */
/* 	{ */
/* 		j = 0; */
/* 		while (pattern[j] == str[i + j] && i + j < len) */
/* 		{ */
/* 			if (pattern[j + 1] == '\0') */
/* 				return ((char *)str + i); */
/* 			j++; */
/* 		} */
/* 		i++; */
/* 	} */
/* 	return (0); */
/* } */

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	j = 0;
	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j] && haystack[i] && i < len)
		{
			i++;
			j++;
		}
		if (!needle[j])
			return ((char *)&haystack[i - j]);
		i = (i - j) + 1;
	}
	return (NULL);
}
/* #include <stdio.h> */
/* int main () { */
/*    const char haystack[20] = "TutorialsPoint"; */
/*    const char needle[10] = "to"; */
/*    char *result; */

/*    result = ft_strnstr(haystack, needle, 4); */
/*    printf("The substring is: %s\n", result); */
/*    return(0); */
/* } */
