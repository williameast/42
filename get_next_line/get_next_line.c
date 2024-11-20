/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:43:53 by William           #+#    #+#             */
/*   Updated: 2024/08/29 12:03:50 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

#include <fcntl.h>
#include <stdio.h>
char	*check_for_null(char *line)
{
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	t_rdr	rdr;

	rdr.bytes_read = 1;
	rdr.index = 0;
	rdr.line = ft_calloc(1, sizeof(char));

	if (BUFFER_SIZE < 1 || fd < 0 || !rdr.line || read(fd, rdr.buf, 0) < 0)
	{
		if (rdr.line)
			free(rdr.line);
		return (NULL);
	}
	while (rdr.bytes_read > 0 && rdr.buf[rdr.index - 1] != '\n')
	{
		ft_bzero(rdr.buf, BUFFER_SIZE + 1);
		rdr.index = 1;
		while (rdr.buf[rdr.index - 1] != '\n' && rdr.bytes_read > 0 &&
			   rdr.index < BUFFER_SIZE + 1)
			rdr.bytes_read = read(fd, rdr.buf + rdr.index++, 1);
		rdr.buf[rdr.index] = '\0';
		rdr.temp = ft_strjoin(rdr.line, rdr.buf + 1);
		free(rdr.line);
		rdr.line = rdr.temp;
	}
	return (check_for_null(rdr.line));
}

int	main(void)
{
	int		fd;
	char	*line;
	int	i;
	i = 0;

	fd = open("test.txt", O_RDONLY);
	while (i < 10)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	return (0);
}
