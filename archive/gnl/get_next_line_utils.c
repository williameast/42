/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:35:24 by William           #+#    #+#             */
/*   Updated: 2024/08/26 14:24:08 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_node	*get_tail(t_node *lst)
{
	t_node	*temp;

	if (!lst)
		return (NULL);

	temp = lst;
	while (temp->link)
		temp = temp->link;

	return(temp);
}

int	get_nl(t_node *lst)
{
	t_node	*tail;
	int	i;

	if (lst == NULL)
		return (0);
	i = 0;
	printf("%s\n", "get_pretail");
	tail = get_tail(lst);

	while(tail->data[i])
	{
		if (tail->data[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	free_list(t_node **lst)
{
	t_node	*temp;

	while (temp != NULL)
	{
		temp = (*lst)->link;
		free(temp->data);
		free(*lst);
		*lst = temp;
	}
	free (*lst);
	*lst = NULL;
}

t_node	*instantiate_or_append_node(t_node **lst, char *data)
{
	t_node	*tail;
	t_node	*result;

	result = malloc(sizeof(t_node));
	printf("t_node size = %lu\n", sizeof(t_node));
	/* result = malloc(sizeof(char *) * 1024); */
	if (result == NULL)
	{
		free(data); // could be removed.
		data = NULL;
		free_list(lst);
		return (NULL);
	}
	printf("pointer of result: %p\n", result);
	printf("%s\n", "instantiated;");
	result->data = data;
	printf("%s\n", "assigned result data");
	result->link = NULL;
	printf("%s\n", "assigned result NULL");

	printf("%p\n", lst);
	if (lst == NULL)
	{
		*lst = result;
		printf("%s\n", "instantiated list is null");
	}

	else
		{
			tail = get_tail(*lst);
			printf("%s\n", "got tail fo lsit");
			printf("pointer of tail_ %p\n", tail);
			tail->link = result;
			printf("%s\n", "instantiated list is NOT null");
		}
	return (*lst);
}

int	get_line_length(t_node *lst)
{
	int	i;
	int	length;
	t_node *temp;

	length = 0;
	temp = lst;
	i = 0;

	while (temp != NULL)
	{
		while (temp->data[i] != '\0')
		{
			length++;
			if (temp->data[i++] == '\n')
				break;
		}
		i++;
		temp = temp->link;
	}
	printf("%s\n", "got line length");
	return (length);
}

