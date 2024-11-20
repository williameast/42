/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:18:23 by William           #+#    #+#             */
/*   Updated: 2024/09/03 15:26:34 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.c"
#include "get_next_line.h"
#include <stdio.h>

char	*generate_line(char *line_prefix)
{
	int	i;
	char	*line;

	if (!line_prefix)
	{
		printf("GENERATE LINE NULL\n");
		return (NULL);
	}
	if (!line_prefix[0])
	{
		printf("GENERATE LINE empty (line[0] == /0)\n");
		return (NULL);
	}
	i = 0;
	while(line_prefix[i] != '\0' && line_prefix[i] != '\n')
		i++;
	if (line_prefix[i] == '\n')
		i++;
	line = (char *)malloc((i * sizeof(char)) + 1);
	if (line == NULL)
	{
		printf("%s\n", "GENERATE LINE: line allocation failed");
		return (NULL);
	}
	i = 0;
	while (line_prefix[i] && line_prefix[i] != '\n')
	{
		line[i] = line_prefix[i];
		i++;
	}
	if (line_prefix[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	printf("GENERATE LINE: line is: %s\n", line);
	return (line);
}

/* char	*offset(char *line_prefix) */
/* { */
/* 	char *new_buffer; */
/* 	int	i; */
/* 	int	j; */

/* 	i = 0; */

/* 	while (line_prefix[i] && line_prefix[i] != '\n') */
/* 		i++; */
/* 	if (line_prefix[i] == '\0') */
/* 	{ */
/* 		free(line_prefix); */
/* 		return (NULL); */
/* 	} */
/* 	i += (line_prefix[i] == '\n'); */
/* 	new_buffer = malloc(1 + ft_strlen(line_prefix) - i); */
/* 	if (!new_buffer) */
/* 		return (NULL); */
/* 	j = 0; */
/* 	while (line_prefix[i + j]) */
/* 	{ */
/* 		new_buffer[j] = line_prefix[i + j]; */
/* 		j++; */
/* 	} */
/* 	new_buffer[j] = '\0'; */
/* 	free(line_prefix); */
/* 	return(new_buffer); */

/* } */

char	*offset_prefix(char *prefix)
{
	char	*out;
	int	i;
	int j;

	if (!prefix)
		return (NULL);
	i = 0;
	while (prefix[i] && prefix[i] != '\n')
		i++;
	if (prefix[i] == '\0')
	{
		free(prefix);
		return (NULL);
	}
	i++;
	out = malloc(( ft_strlen(prefix) - i + 1 ) * sizeof(char));
	if (!out)
	{
		free(prefix);
		return (NULL);
	}
	j = 0;
	while (prefix[i + j] != '\0')
	{
		out[j] = prefix[i + j];
		j++;
	}
	out[j] = '\0';
	free(prefix);
	return (out);
}

#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	int	bytes_read;
	char	*read_buffer;
	static char	*line_prefix;


	/* printf("%s\n", "entering malloc stage"); */
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		printf("EXIT: fd: %i, BUFFER_SIZE = %i\n", fd, BUFFER_SIZE);
		return (NULL);
	}
	read_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (read_buffer == NULL)
		return (NULL);
	bytes_read = 1;
	/* printf("%s\n", "entering while loop"); */
	while (!ft_strchr(line_prefix, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		line_prefix = ft_strjoin(line_prefix, read_buffer);
	}
	free(read_buffer);
	read_buffer = generate_line(line_prefix);
	line_prefix = offset_prefix(line_prefix);
	return (read_buffer);
}


int	main(void)
{
	int		fd;
	char	*line;
	int	i;
	i = 0;

	fd = open("test.txt", O_RDONLY);
	while (i < 5)
	{
		line = get_next_line(fd);
		printf("--------------- ACTUAL OUTPUT: %s", line);
		free(line);
		i++;
	}
	return (0);
}
