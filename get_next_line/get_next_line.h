/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:56:09 by William           #+#    #+#             */
/*   Updated: 2024/08/29 11:52:35 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1
# endif

typedef struct s_rdr
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	char	*line;
	int		index;
	int		bytes_read;
}			t_rdr;

/* char	*get_next_line(int fd); */
/* size_t	ft_strlen(const char *str); */
/* char	*ft_strjoin(char const *s1, char const *s2); */
/* void	*ft_memmove(void *dst, const void *src, size_t len); */
/* void	ft_bzero(void *s, size_t n); */
/* void	*ft_calloc(size_t count, size_t size); */
/* char	*return_value(char	*res); */

#endif
