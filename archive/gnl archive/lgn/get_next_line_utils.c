/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:46:03 by William           #+#    #+#             */
/*   Updated: 2024/09/06 11:23:48 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	if (!s)
	{
		/* printf("%s\n", "STRLEN: measured string is NULL, returning 0"); */
		return (0);
	}
	int	len;
	len = 0;
	while (s[len])
		len++;
	return(len);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != '\0' && *str != c)
		str++;
	if (*str == c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			result[i] = s1[i];
			i++;
		}
	}
	while (s2[j] != '\0')
		result[i++] = s2[j++];
	result[i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (result);
}

void	add_node(t_lst **list ,char *data)
{
	t_lst	*temp;
	t_lst	*new_node;

	new_node = (t_lst *)malloc(sizeof(t_lst));
	if (!new_node)
		return ;
	new_node->buffer = ft_strjoin(NULL, data);
	new_node->nl_pos = ft_strchr(data, '\n');
	new_node->link = NULL;
	if(*list == NULL)
	{
		/* printf("ADD_NODE: no list found. generating a new list with data <%s>\n", data); */
		*list = new_node;
		return ;
	}
	temp = *list;
	while(temp->link != NULL)
		temp = temp->link;
	temp->link = new_node;
	/* printf("ADD_NODE: new node added at the end of list with data <%s>\n", data); */
	return ;
}

void	free_list(t_lst **list)
{
	t_lst	*temp;
	t_lst	*next;

	temp = *list;
	while (temp)
	{
		next = temp->link;
		free(temp->buffer);
		free(temp);
		temp = next;
	}
	*list = NULL;
}
