/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:35:32 by weast             #+#    #+#             */
/*   Updated: 2024/06/30 17:15:49 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}

/* char	*ft_strtrim(const char *str, const char *pattern) */
/* { */
/* 	int		start; */
/* 	int		end; */
/* 	int		i; */
/* 	char	*result; */

/* 	if (!str || !pattern) */
/* 		return (NULL); */
/* 	start = 0; */
/* 	i = 0; */
/* 	end = ft_strlen(str) - 1; */
/* 	while (ft_strchr(pattern, str[start]) && start <= end) */
/* 		start++; */
/* 	if (start > end) */
/* 		return (ft_strdup(str + end + 1)); */
/* 	while (ft_strchr(pattern, str[end]) && end >= 0) */
/* 		end--; */
/* 	result = (char *)malloc(sizeof(char) * end - start); */
/* 	if (!result) */
/* 		return (NULL); */
/* 	while (start <= end) */
/* 	{ */
/* 		result[i] = str[start]; */
/* 		i++; */
/* 		start++; */
/* 	} */
/* 	return (result); */
/* } */

/* #include <stdio.h> */
/* int main(void) */
/* { */
/* printf("%s\n", ft_strtrim("...this is a test...", ".")); */
/*     return 0; */
/* } */
