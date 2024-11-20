/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_link_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikito                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:57:36 by nikito            #+#    #+#             */
/*   Updated: 2024/08/28 09:24:10 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_node	*lst = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_and_save(fd, &lst);
	if (lst == NULL)
		return (NULL);
	extract_line(lst, &line);
	extract_remainder_and_free(&lst);
	if (line[0] == '\0')
	{
		free_lst(lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_save(int fd, t_node **lst)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!check_for_newline(*lst) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if ((*lst == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		add_to_lst(lst, buf, readed);
		free(buf);
	}
}

void	add_to_lst(t_node **lst, char *buf, int readed)
{
	int		i;
	t_node	*last;
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return ;
	new_node->link = NULL;
	new_node->data = malloc(sizeof(char) * (readed + 1));
	if (new_node->data == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->data[i] = buf[i];
		i++;
	}
	new_node->data[i] = '\0';
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	last = get_tail(*lst);
	last->link = new_node;
}

void	extract_line(t_node *lst, char **line)
{
	int	i;
	int	j;

	if (lst == NULL)
		return ;
	generate_line(line, lst);
	if (*line == NULL)
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->data[i])
		{
			if (lst->data[i] == '\n')
			{
				(*line)[j++] = lst->data[i];
				break ;
			}
			(*line)[j++] = lst->data[i++];
		}
		lst = lst->link;
	}
	(*line)[j] = '\0';
}

void	extract_remainder_and_free(t_node **lst)
{
	t_node	*last;
	t_node	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = malloc(sizeof(t_node));
	if (lst == NULL || temp == NULL)
		return ;
	temp->link = NULL;
	last = get_tail(*lst);
	while (last->data[i] != '\0' && last->data[i] != '\n')
		i++;
	if (last->data[i] == '\0' && last->data[i] == '\n')
		i++;
	temp->data = malloc(sizeof(char) * ((ft_strlen(last->data) - i) + 1));
	if (temp->data == NULL)
		return ;
	while (last->data[i])
		temp->data[j++] = last->data[i++];
	free_lst(*lst);
	temp->data[j] = '\0';
	*lst = temp;
}
