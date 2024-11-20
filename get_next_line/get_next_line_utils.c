/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:54:15 by William           #+#    #+#             */
/*   Updated: 2024/08/29 10:33:09 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int len;
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n)
	{
		*ptr++ = 0;
		--n;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

void *ft_memmove(void *dest, const void *source, size_t n)
{
    char *temp_source;
    char *temp_dest;
	size_t	i;

    if (!dest && !source)
		return (0);
	i = 0;
    temp_source = (char *)source;
    temp_dest = (char *)dest;
    if (temp_source > temp_dest)
    {
		while (i < n)
		{
			temp_dest[i] = temp_source[i];
			i++;
		}
    }
    else
    {
        while (n--)
			temp_dest[n] = temp_source[n];
    }
    return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (!res)
		return (NULL);
	ft_memmove((void *) res, (void *) s1, len_s1);
	ft_memmove((void *) res + len_s1, (void *) s2, len_s2 + 1);
	return (res);
}
