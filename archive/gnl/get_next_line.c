/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:08:01 by William           #+#    #+#             */
/*   Updated: 2024/08/26 14:26:40 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.c"

int	ft_strlen(const char *str)
{
    int	i;

    i = 0;
    while(str[i] != '\0')
        i++;
    return(i);
}
void	read_lines(int	fd, t_node *lst)
{
	char *buffer;
	int	bytes_read;

	while (!get_nl(lst))
	{
		buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return(free_list(&lst));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free(buffer));
		buffer[bytes_read] = '\0';
		if (!instantiate_or_append_node(&lst, buffer))
		return;
	}
}

void	get_full_line(t_node *lst, char **line)
{

	int	len;
	t_node	*temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	temp = lst;
	len = get_line_length(lst);
	if (!len)
		return ;
	*line = malloc(sizeof(char *) * (len + 1));
	if (!line)
		return (free_list(&lst));

	while (temp != NULL)
	{
		while(temp->data[i] && j < len)
			*line[i++] = temp->data[j++];
		i = 0;
		temp = temp->link;
	}
	*line[i] = '\0';
}

void	get_remainder(t_node **lst)
{
	t_node *tail;
	char	*data;
	int	prev;
	int	i;
	int	len;

	tail =	get_tail(*lst);
	len = 0;
	i = 0;
	prev = get_line_length(tail);
	while (tail->data + prev + len)
		len++;
	if (!len)
		return (free_list(lst));
	data = malloc(sizeof(char *) * (len + 1));
	if (data == NULL)
		return (free_list(lst));
	while ((tail->data + prev) && i < len)
		data[i++] = *tail->data + prev++;
	data[i] = '\0';
	free_list(lst);
	if (!instantiate_or_append_node(lst, data))
		return ;
}
void debug_print_full_node(t_node **head)
{
	int	len;
	char *result;
	t_node	*temp;
	int	i;
	int	result_index;

	temp = *head;
	len = 0;
	result_index = 0;
	while(temp != NULL)
	{
		len += ft_strlen(temp->data);
		temp = temp->link;
	}

    result = (char *)malloc(len + 1);  // Allocate memory for the result string
    if (result == NULL)
		return (NULL);
	temp = *head;
	while (temp != NULL)
	{
		i = 0;
		while(temp->data[i] != '\0')
		{
			result[result_index] = temp->data[i];
			result_index++;
			i++;
		}
		temp = temp->link;
	}
	result[len] = '\0';
	free(temp);
	printf("%s\n", result);
	free(result);
}


char	*get_next_line(int fd)
{
	static t_node	*lst = NULL;
	char	*line;

	line = NULL;
	if (read(fd, line, 0) < 0)
	{
		free_list(&lst);
		return (NULL);
	}
	else if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);

	read_lines(fd, lst);

	if (lst == NULL)
		return (NULL);
	get_full_line(lst, &line);
	if (!lst)
		return (NULL);
	get_remainder(&lst);

	return (line);
	}


#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(void) {
	int	fd;
    int	i = 0;
	char	*line;

	char *filename = "test.txt";

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("%s could not be found.", filename));
	else {
		printf("read file at fd: %i\n", fd);
	}

    while (i < 2)
    {
		printf("%i\n", i);
        line = get_next_line(fd);
		printf("%i, %p\n", i, line);
		if (line != NULL)
			printf("%s\n", line);
		/* if (line != NULL) */
		/* { */
		/* 	printf("line %d, %s  \n", i, line); */
		/* 	free(line); */
		/* 	printf("_______ BREAK _______ \n"); */
		/* } */
        i++;
    }
    close(fd);

    return 0;
}
