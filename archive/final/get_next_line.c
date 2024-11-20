/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:57:55 by William           #+#    #+#             */
/*   Updated: 2024/08/27 22:15:35 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
int check_for_nl(t_node **lst)
{
    t_node  *temp;
    int     i;

	printf("%s\n", "checked nl");
    temp = *lst;
    while (temp != NULL)
    {
        i = 0;
        while (temp->buffer[i] != '\0')
        {
            if (temp->buffer[i] == '\n')
			{
				printf("%s\n", "nl found");
				return (1);
			}
            i++;
        }
        temp = temp->link;  // Move to the next node.
    }
	printf("%s\n", "no nl found");
    return (0);  // Newline not found in any buffer.
}

t_node	*get_tail(t_node *lst)
{
	t_node	*temp;

	temp = lst;
	while (temp && temp->link)
		temp = temp->link;
	return (temp);
}

void	generate_line(t_node *lst, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->buffer[i])
		{
			if (lst->buffer[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		lst = lst->link;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	append_node(t_node **lst, char *data, int bytes_read)
{
	int	i;
	t_node *tail;
	t_node *new_node;
	printf("%s\n", "attempting to add a new node");

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return ;
	new_node->link = NULL;
	new_node->buffer = malloc(sizeof(char) * bytes_read + 1);
	if (new_node->buffer == NULL)
		return ;
	i = 0;
	while (data[i] == '\0' && i < bytes_read)
	{
		new_node->buffer[i] = data[i];
		i++;
	}
	new_node->buffer[i] = '\0';
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	tail = get_tail(*lst);
	tail->link = new_node;
}

void	debug_print_full_node(t_node **lst)
{
	t_node *temp = *lst;

	while (temp)
	{
		printf("DEBUG: <%s>\n", temp->buffer);
		temp = temp->link;
	}
}

void save_line(t_node **lst, int fd)
{
	int	bytes_read;
	char	*buffer;

	bytes_read = 1;
	while (!check_for_nl(lst) && bytes_read > 0)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		printf("%s\n", "im iun the loop!");
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((*lst == NULL && bytes_read == 0) || bytes_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		append_node(lst, buffer, bytes_read);
		free(buffer);
	}
	debug_print_full_node(lst);
}

void	extract_line(t_node *lst, char **line)
{
	int	i;
	int	j;
	if (lst == NULL)
		return;
	extract_line(lst, line);
	if (*line == NULL)
		return;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->buffer[i] != '\0')
		{
			if (lst->buffer[i] == '\n')
			{
				(*line)[j++] = lst->buffer[i];
				break;
			}
			(*line)[j++] = lst->buffer[i++];
		}
		lst = lst->link;
	}
	(*line)[j] = '\0';
}

char	*get_next_line(int fd)
{
	static t_node	*lst = NULL;
	char *line;

	line = NULL;
	//check we are ready to go.
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, line, 0))
		return (NULL);

	// read list.
	printf("%s\n", "entering saveliine");
	save_line(&lst, fd);

	/* catch_remainder(&lst); */

	/* if (line[0] == '\0') */
	/* 	//free list. */
	/* 	return (NULL); */

	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break ;
		free(line);
	}
	return (0);
}
