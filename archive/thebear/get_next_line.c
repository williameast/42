/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:28:38 by William           #+#    #+#             */
/*   Updated: 2024/08/27 19:47:49 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include "get_next_line_utils.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	debug_print_full_node(t_node **lst)
{
	t_node *temp = *lst;

	while (temp)
	{
		printf("DEBUG: <%s>\n", temp->buffer);
		temp = temp->link;
	}
}


size_t	ft_strcat(char *dest, const char *src)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j])
		j++;
	while (src[k])
	{
		dest[j + k] = src[k];
		k++;
	}
	dest[j + k] = '\0';
	return (j + k);

}

/* char *generate_line(t_node **lst, char *remainder) */
/* { */
/* 	int	len; */
/* 	char	*line; */
/* 	t_node	*temp; */

/* 	temp = *lst; */
/* 	len = 0; */
/* 	while (temp != NULL) // does this work for shorter strings? */
/* 	{ */
/* 		len += ft_strlen(temp->buffer); */
/* 		temp = temp->link; */
/* 	} */
/* 	line = malloc(sizeof(char *) * (len + 1)); */
/* 	if (!line) */
/* 		return NULL; */
/* 	line[0] = '\0'; */
/* 	temp = *lst; */
/* 	while (temp != NULL) */
/* 	{ */
/* 		ft_strcat(line, temp->buffer); */
/* 		temp = temp->link; */
/* 	} */
/* 	if (remainder != NULL) */
/* 	{ */
/* 		line[ft_strlen(line) - ft_strlen(remainder) + 1] = '\0'; */
/* 		printf("remainder is: %s\n", remainder); */
/* 		/\* *lst = instantiate_node(remainder); *\/ */
/* 	} */
/* 	printf("PRINTED LINE: %s", line); */
/* 	return (line); */
/* } */

/* char	*get_next_line(int fd) */
/* { */
/* 	//why double pointer for t_list */

/* 	// while there is no \n character in the last node of the buffer */
/* 	// allocate buffer size of BUFFER_SIZE (if fail, clear all nodes) */
/* 	// read in the bytes read(fd, buffer, BUFFER_SIZE) */
/* 	// if bytes_read = 0 */
/* 	// free buffer and return */

/* 	static t_node *lst = NULL; */
/* 	char	*buffer; */
/* 	int	bytes_read; */
/* 	char	*line; */
/* 	char	*newline_pos; */

/* 	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); */
/* 	if (!buffer) */
/* 		return (NULL); */
/* 	line = NULL; */
/* 	while (1) */
/* 	{ */
/* 		bytes_read = read(fd, buffer, BUFFER_SIZE); */
/* 		if (bytes_read <= 0) */
/* 		{ */
/* 			free(buffer); */
/* 			line = generate_line(&lst, NULL); */
/* 		} */
/* 		buffer[bytes_read] = '\0'; */
/* 		append_node(&lst, buffer); */
/* 		if (ft_strchr(lst->buffer, '\n')) */
/* 			/\* printf("%s\n", "I have detected a new line in the first lst buffer."); *\/ */
/* 		newline_pos = ft_strchr(buffer, '\n'); */
/* 		/\* printf("newline pos is: %s\n", newline_pos); *\/ */
/* 		if (ft_strchr(lst->buffer, '\n') != NULL) */
/* 		{ */
/* 			printf("%s\n", "detected n in first list item."); */
/* 			line = generate_line(&lst, ft_strchr(lst->buffer, '\n')); */
/* 			lst = instantiate_node(ft_strchr(lst->buffer, '\n') + 1); */
/* 			/\* debug_print_full_node(&lst); *\/ */
/* 			break; */
/* 		} */
/* 		else if (newline_pos != NULL) */
/* 		{ */
/* 			printf("%s\n", "detected n in read buffer."); */
/* 			line = generate_line(&lst, newline_pos); */
/* 			lst = instantiate_node(newline_pos + 1); */
/* 			/\* printf("%s\n", "this is the new lst."); *\/ */
/* 			/\* debug_print_full_node(&lst); *\/ */
/* 			break; */
/* 		} */
/* 	} */
/* 	return (line); */
/* } */


/* int get_len_until_nl(t_node *lst) */
/* { */
/* 	int	i; */
/* 	int len; */
/* 	t_node	*temp; */

/* 	temp = lst; */
/* 	i = 0; */
/* 	len = 0; */

/* 	while (temp != NULL) */
/* 	{ */
/* 		while(temp->buffer[i] != '\0') */
/* 		{ */
/* 			len++; */
/* 			if (temp->buffer[i++] == '\n') */
/* 				break; */
/* 		} */
/* 		i = 0; */
/* 		temp = temp->link; */
/* 	} */
/* 	return (len); */
/* } */

/* char	*gen_line(t_node **lst) */
/* { */
/* 	t_node *temp; */
/* 	char	*line; */
/* 	int	len; */
/* 	int i; */

/* 	len = get_len_until_nl(*lst); */
/* 	line = malloc(sizeof(char) * (len + 1)); */
/* 	i = 0; */
/* 	if (!line) */
/* 		return (NULL); */
/* 	line[0] = '\0'; */
/* 	temp = *lst; */
/* 	while (temp->link != NULL) */
/* 	{ */
/* 		strcat(line, temp->buffer); */
/* 		temp = temp->link; */
/* 	} */
/* 	if (ft_strchr(temp->buffer, '\n') != NULL) */
/* 	{ */
/* 		while (temp->buffer[i] != '\n') */
/* 		{ */
/* 			line[len] = temp->buffer[i]; */
/* 			i++; */
/* 			len++; */
/* 		} */
/* 	} */
/* 	else */
/* 		strcat(line, temp->buffer); */
/* 	return (line); */
/* } */

int	get_full_length(t_node **lst)
{
	t_node *temp;
	int	len;

	temp = *lst;
	len = 0;

	while (temp != NULL)
	{
		len += ft_strlen(temp->buffer);
		temp = temp ->link;
	}
	return (len);
}

int check_for_nl(t_node **lst)
{
    t_node  *temp;
    int     len;
    int     i;

    len = 0;
    temp = *lst;

    while (temp != NULL)
    {
        i = 0;
        while (temp->buffer[i] != '\0')
        {
            if (temp->buffer[i] == '\n')
                return (len + i);  // Newline found, return its position.
            i++;
        }
        len += ft_strlen(temp->buffer);  // Add length of the current buffer.
        temp = temp->link;  // Move to the next node.
    }
    return (-1);  // Newline not found in any buffer.
}

char *generate_line(t_node **lst, int nl_pos)
{

	t_node	*temp;
	char *line;
	int	i;
	int j;

	i = 0;
	j = 0;
	temp = *lst;
	if (nl_pos == -1)
		nl_pos = get_full_length(lst);
	line = malloc(sizeof(char) * nl_pos);
	while (temp != NULL)
	{
		while (temp->buffer[j] != '\0' && i < nl_pos)
		{
			line[i] = temp->buffer[j];
			i++;
			j++;
		}
		j = 0;
		temp = temp->link;
	}
	line[i] = '\0';
	return (line);
}
char	*get_next_line(int fd)
{
	// NULL list to begin with.
	static t_node *lst = NULL;
	char	*line;
	int	bytes_read;
	char	*temp_buffer;
	int	nl_pos;

	line = NULL;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);

	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			temp_buffer[bytes_read] = '\0';
			nl_pos = check_for_nl(&lst);
			append_node(&lst, temp_buffer);
			if (nl_pos != -1)
				break;
		}
	}
	line = generate_line(&lst, nl_pos);

	/* if (nl_pos != -1) */
	/* { */
	/* 	lst = instantiate_node(ft_strchr(temp_buffer, '\n')); */
	/* } */
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
int main(void) {

	int	i = 0;
	char *line;
	int	fd;
	char *filename = "test.txt";

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("%s could not be found.", filename));
	/* else { */
	/* 	/\* printf("READ:read file at fd: %i\n", fd); *\/ */
	/* } */

    while (i < 10)
    {
        line = get_next_line(fd);
		printf("line %i: %s", i + 1, line);
		printf("%s\n", "BREAK _______________________________");
		free(line);
        i++;
    }
    close(fd);
    return 0;
}
