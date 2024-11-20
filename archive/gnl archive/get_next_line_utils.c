/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikito                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 07:57:36 by nikito            #+#    #+#             */
/*   Updated: 2024/08/28 09:22:59 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

int	check_for_newline(t_node *lst)
{
	int		i;
	t_node	*current;

	if (lst == NULL)
		return (0);
	current = get_tail(lst);
	i = 0;
	while (current->data[i])
	{
		if (current->data[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_node	*get_tail(t_node *lst)
{
	t_node	*current;

	current = lst;
	while (current && current->link)
		current = current->link;
	return (current);
}

void	generate_line(char **line, t_node *lst)
{
	int	i;
	int	len;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->data[i])
		{
			if (lst->data[i] == '\n')
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

void	free_lst(t_node *lst)
{
	t_node	*current;
	t_node	*link;

	current = lst;
	while (current)
	{
		free(current->data);
		link = current->link;
		free(current);
		current = link;
	}
}
