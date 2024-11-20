/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:44:27 by William           #+#    #+#             */
/*   Updated: 2024/08/27 20:45:17 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>



int	check_for_nl(t_node *lst)
{
	int	i;
	t_node *temp;

	if (lst == NULL)
		return (0);

	temp = lst;
	i = 0;
	while (temp->link == NULL)
	{
		if (temp->buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

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

t_node	*instantiate_node(const char *data, int bytes_read)
{
    t_node	*new_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (new_node == NULL)
		return (NULL);
	new_node->buffer = malloc(sizeof(char) * (bytes_read + 1));
	if (new_node->buffer == NULL)
		return ;
	i = 0;
	while (data[i] != '\0' && i < bytes_read)
	{
		new_node->buffer[i] = data[i];
		i++;
	}
	new_node->buffer[i] = '\0';
	return (new_node);
}

void	append_node(t_node **lst,const char *data, int bytes_read)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = instantiate_node(data, bytes_read);

	if (*lst == NULL)
		*lst = new_node;
	else
	{
	temp = *lst;
	while (temp->link != NULL)
		temp = temp->link;
	temp->link = new_node;
	}
	return ;
}
