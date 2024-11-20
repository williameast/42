/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cannoli.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:28:56 by William           #+#    #+#             */
/*   Updated: 2024/08/23 18:25:18 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_utils.c"
#include <stdio.h>
int	get_line_length(t_node **head)
{
	t_node	*temp;
	int	len;

	temp = *head;
	len = 0;

	/* printf("----------------------------------------------------------------------------\n"); */
	/* printf("GET_LINE_LEN:\n"); */
	while (temp != NULL)
	{
		if (temp->nl_pos == -1)
			len += ft_strlen(temp->buffer);
		else
		{
			len += temp->nl_pos;
			break;
		}
		temp = temp->link;
	}

	printf("length of %i calculated.\n", len);
	return (len);
}
/* ************************************************************************** */
void debug_print_full_node(t_node **head)
{
	int	len;
	char *result;
	t_node	*temp;
	int	i;
	int	result_index;
	int	counter;

	counter = 0;
	temp = *head;
	len = 0;
	result_index = 0;
	while(temp != NULL)
	{
		len += ft_strlen(temp->buffer);
		temp = temp->link;
	}

    result = (char *)malloc(len + 1);  // Allocate memory for the result string
    /* if (result == NULL) */
	/* 	return (NULL); */
	temp = *head;
	while (temp != NULL)
	{
		i = 0;
		while(temp->buffer[i] != '\0')
		{
			result[result_index] = temp->buffer[i];
			result_index++;
			i++;
		}
		counter++;
		printf("node %i, NL present at: %i, contents:\n%s\n", counter, temp->nl_pos, temp->buffer);
		temp = temp->link;
	}
	result[len] = '\0';
	free(temp);
	printf("RESULT:\n%s\n", result);
	free(result);
}
/* ************************************************************************** */

t_node	*instantiate_node(const char *data)
{
    t_node	*new_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (new_node == NULL)
        return (NULL);
    new_node->buffer[0] = '\0';
    ft_strlcat(new_node->buffer, data, BUFFER_SIZE + 1);
	if (ft_strchr(data, '\n'))
		new_node->nl_pos = ft_strchr(data, '\n') - data;
	else
		new_node->nl_pos = -1;
    new_node-> link = NULL;
	/* printf("----------------------------------------------------------------------------\n"); */
	/* printf("INSTANTIATE_NODE:\n created new node, contents:\n <%s>\n length: %i\n", new_node->buffer, ft_strlen(new_node->buffer)); */
	return (new_node);
}

void	append_node(t_node **head, const char *data)
{

	t_node	*new_node;
	t_node	*temp_node;
	int	counter;

	new_node = instantiate_node(data);
	counter = 0;

	if (*head == NULL)
		*head = new_node;
	else
	{
		temp_node = *head;
		while (temp_node->link != NULL)
		{
			temp_node = temp_node->link;
			counter++;
		}
		temp_node->link = new_node;
		/* printf("----------------------------------------------------------------------------\n"); */
		/* printf("APPEND_NODE:\n new node added, at position %i\n", counter); */
	}
}


char *extract_line(t_node **head)
{
    t_node *temp = *head;
    char *result;
    int result_index = 0;
    int buffer_index = 0;

    result = (char *)malloc(get_line_length(head) + 1);
    if (!result)
        return NULL;

    while (temp != NULL)
    {
        buffer_index = 0;
        if (temp->nl_pos != -1) // if a newline is found
        {
            while (buffer_index <= temp->nl_pos)
            {
                result[result_index] = temp->buffer[buffer_index];
                buffer_index++;
                result_index++;
            }
            result[result_index] = '\0';

            // Update head to the remainder of the current buffer
            *head = instantiate_node(temp->buffer + temp->nl_pos + 1);
            free(temp);
            return result;
        }
        else
        {
            while (temp->buffer[buffer_index] != '\0')
            {
                result[result_index] = temp->buffer[buffer_index];
                buffer_index++;
                result_index++;
            }
            result[result_index] = '\0';
        }

        *head = temp->link;
        free(temp);
        temp = *head;
    }
    result[result_index] = '\0';
    return result;
}

char *get_next_line(int fd)
{
	static	t_node *head = NULL;
	char buffer[BUFFER_SIZE + 1];
	int	bytes_read;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		/* printf("appending: %s, bytes read: %i\n", buffer, bytes_read); */
		append_node(&head, buffer);
	}

	/* debug_print_full_node(&head); */

	return extract_line(&head);
}

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int	fd;
    int	i = 0;
	char	*line;

	char *filename = "test.txt";

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("%s could not be found.", filename));

	/* get_next_line(fd); */

    while (i < 10)
    {
        line = get_next_line(fd);
		if (line != NULL)
		{
			printf("line %d <%s>  \n", i, line);
			free(line);
			printf("_______ BREAK _______ \n");
		}
        i++;
		}
    close(fd);
    return 0;
}
