/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:44:27 by William           #+#    #+#             */
/*   Updated: 2024/08/27 11:30:50 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(const char *str) //up to nl!!!!
{
	int	i;

	i = 0;
	while(str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(*s1) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	while(s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	str[i] = 0;
	return (str);

}

char	*ft_strchr(const char *str, char c)
{
	while (*str != '\0' && *str != c)
		str++;
	if (*str == c)
		return ((char *)str);
	return (NULL);
}

t_node	*instantiate_node(const char *data)
{
    t_node	*new_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (new_node == NULL)
		return (NULL);
	new_node->buffer = ft_strdup(data);
	if (!new_node->buffer)
	{
		free(new_node);
		return(NULL);
	}
    new_node-> link = NULL;
	return (new_node);
}

void	append_node(t_node **lst,const char *data)
{
	t_node	*new_node;
	t_node	*temp;

	if (!(*lst))
	{
		*lst = instantiate_node(data);
		return;
	}
	new_node = instantiate_node(data);
	if (!new_node)
		return;
	temp = *lst;
	while (temp->link != NULL)
		temp = temp->link;
	temp->link = new_node;
}
