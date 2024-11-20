/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:42:19 by weast             #+#    #+#             */
/*   Updated: 2024/07/08 16:37:04 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_words(const char *str, char delimiter)
{
	size_t	i;
	size_t	wordcount;
	int		flag;

	i = 0;
	wordcount = 0;
	flag = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == delimiter)
			flag = 0;
		else if (flag == 0)
		{
			wordcount++;
			flag = 1;
		}
		i++;
	}
	return (wordcount);
}

static int	get_word_length(const char *s, unsigned int start, char c)
{
	int	i;

	i = start;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i - start);
}

static int	free_layered(char **arr, int j)
{
	while (j > 0)
		free(arr[--j]);
	free(arr);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	size_t	i;
	int		j;

	arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			arr[j++] = ft_substr(s, i, get_word_length(s, i, c));
			if (!arr[j - 1])
				free_layered(arr, j - 1);
			i += get_word_length(s, i, c);
		}
	}
	arr[j] = NULL;
	return (arr);
}
/* #include <stdio.h> */
/* int main(void) { */
/* 	char *str = "hello!"; */
/* 	char **res = ft_split(str, ' '); */
/* 	int i = 0; */
/* 	if (res) { */
/* 		while (res[i] != NULL) */
/* 		{ */
/* 			printf("%s\n", res[i]); */
/* 			free(res[i]); */
/* 			i++; */
/* 		} */
/* 		free(res); */
/* 	} */
/* 	return 0; */
/* } */
