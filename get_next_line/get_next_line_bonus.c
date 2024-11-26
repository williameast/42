/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:52:00 by weast             #+#    #+#             */
/*   Updated: 2024/09/17 12:17:18 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*generate_line(char *start)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (start[i] && start[i] != '\n')
		i++;
	if (!start[i])
	{
		free(start);
		return (NULL);
	}
	line = malloc((ft_strlen(start) - i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i++;
	while (start[i])
		line[j++] = start[i++];
	line[j] = '\0';
	free(start);
	return (line);
}

char	*read_file(int fd, char *start)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 888;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (bytes_read != 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(start);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		start = ft_strjoin(start, buffer);
	}
	free(buffer);
	return (start);
}

char	*get_next_line(int fd)
{
	static char	*start;
	char		*line;
	int			i;

	line = NULL;
	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	start = read_file(fd, start);
	if (!start)
		return (NULL);
	if (*start)
	{
		while (start[i] && start[i] != '\n')
			i++;
		line = malloc(sizeof(char) * i + 2);
		if (!line)
			return (NULL);
		line = ft_strcpy(line, start);
	}
	start = generate_line(start);
	return (line);
}
