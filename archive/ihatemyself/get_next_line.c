/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:15:36 by William           #+#    #+#             */
/*   Updated: 2024/08/27 20:55:24 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"
#include <fcntl.h>


read_and_store_remainder(int fd, t_node **lst)
{
	char *buffer;
	int	bytes_read;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while(check_for_nl(*lst) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*lst == NULL && bytes_read < 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';

	}
}

void generate_line(t_node *lst, char **line)
{
	int i;
	int j;

	if (lst == NULL)
		return ;
	if (*line == NULL)
		return ;
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

clean_lst(t_node **lst)
{
	t_node	*last;
	t_node	*temp;

	t_node	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->link = NULL;

	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}
