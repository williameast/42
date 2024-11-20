/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:30:20 by weast             #+#    #+#             */
/*   Updated: 2024/08/26 17:53:51 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, char c)
{
	while (*str != '\0' && *str != c)
		str++;
	if (*str == c)
		return ((char *)str);
	return (NULL);
}

int	ft_strlen(const char *str)
{
    int	i;

    i = 0;
    while(str[i] != '\0')
        i++;
    return(i);
}

char	*ft_strcpy(char *dest, const char *src)
{
    int	i;

    if(dest == NULL || src == NULL)
        return (NULL);
    i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return(dest);
}
size_t	ft_strcat(char *dest, const char *src)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j])
		j++;
	while (src[k])
	{
		dest[j + k] = src[k];
		k++;
	}
	dest[j + k] = '\0';
	return (j + k);

}
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
	return (j + ft_strlen(src));
}
/* char	*ft_strjoin(const char *s1, const char *s2) */
/* { */
/* 	size_t	i; */
/* 	size_t	j; */
/* 	char	*result; */

/* 	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char)); */
/* 	if (!result) */
/* 		return (NULL); */
/* 	i = 0; */
/* 	j = 0; */
/* 	while (s1[i] != '\0') */
/* 	{ */
/* 		result[i] = s1[i]; */
/* 		i++; */
/* 	} */
/* 	while (s2[j] != '\0') */
/* 	{ */
/* 		result[i] = s2[j]; */
/* 		j++; */
/* 		i++; */
/* 	} */
/* 	result[i] = '\0'; */
/* 	return (result); */
/* } */
/* int	get_list_length(t_node *node) */
/* { */
/*     int	i; */

/*     i = 0; */
/*     while (node->link != NULL) */
/*     { */
/*         node = node->link; */
/*         i++; */
/*     } */
/*     return (i); */
/* } */

/* int	get_list_buffer_length(t_node *node) */
/* { */
/*     int	length; */

/*     length = 0; */
/*     while (node->link != NULL) */
/*     { */
/*         length += ft_strlen(node->buffer); */
/*         node = node->link; */
/*     } */
/*     return (length); */
/* } */

/* void	free_list(t_node *node) */
/* { */
/*     t_node	temp; */

/*     while(node != NULL) */
/*         { */
/*             temp = *node->link; */
/*             free(node); */
/*             *node = temp; */
/*         } */
/*     node = NULL; */
/* } */

#include <stdio.h>
int main(void) {

	printf("%s\n", "hello");

    return 0;
}
