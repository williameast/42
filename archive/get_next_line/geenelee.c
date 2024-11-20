/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geenelee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:07:26 by William           #+#    #+#             */
/*   Updated: 2024/08/26 15:10:49 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.c"
#include <stdio.h>

t_node	*instantiate_node(const char *data)
{
    t_node	*new_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (new_node == NULL)
        return (NULL);
    new_node->buffer[0] = '\0';
    ft_strlcat(new_node->buffer, data, BUFFER_SIZE + 1);
    new_node-> link = NULL;
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
	{
		*head = new_node;
		/* printf("APPEND_NODE:\n head = new node.\n"); */
	}

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
		if (ft_strchr(temp->buffer, '\n'))
		{
			len += (ft_strchr(temp->buffer, '\n') - temp->buffer);
			break;
		}
		else
			len+=ft_strlen(temp->buffer);
		temp = temp->link;
	}

	/* printf("length of %i calculated.\n", len); */
	return (len);
}



/* char	*extract_line(t_node **head) */
/* { */
/* 	t_node *temp = *head; */
/* 	int	max_len = 0; */
/* 	int current_len = 0; */

/* 	while (temp) */
/* 	{ */
/* 		max_len += ft_strlen(temp->buffer); */
/* 		temp = temp->link; */
/* 	} */

/* 	if (max_len == 0) */
/* 		return (NULL); */

/* 	char *result = (char * )malloc(max_len + 1); */
/* 	if (result == NULL) */
/* 		return (NULL); */

/* 	temp = *head; */
/* 	while (temp) */
/* 	{ */
/* 		int	i = 0; */
/* 		while (temp->buffer[i]) */
/* 		{ */
/* 			result[current_len++] = temp->buffer[i]; */
/* 			if (temp->buffer[i] == '\n') */
/* 			{ */
/* 				result[current_len] = '\0'; */
/* 				*head = instantiate_node(temp->buffer + i + 1); */
/* 				return result; */
/* 			} */
/* 			i++; */
/* 		} */
/* 		temp = temp->link; */
/* 	} */
/* 	result [current_len] = '\0'; */
/* 	*head = NULL; */
/* 	return result; */
/* } */


char *extract_line(t_node **head)
{
    t_node *temp;
    int len;
    int i;
    int result_index;
    char *result;


	/* printf("----------------------------------------------------------------------------\n"); */
	/* printf("EXTRACT_LINE:\n"); */
    len = get_line_length(head);  // Calculate the length of the line to extract
    result = (char *)malloc(len + 1);  // Allocate memory for the result string
    if (result == NULL || len == 0)
        return (NULL);
    temp = *head;
    result_index = 0;
    while (temp != NULL)
    {
        i = 0;
        while (temp->buffer[i] != '\0')
        {
            result[result_index] = temp->buffer[i];
            result_index++;
            if (temp->buffer[i] == '\n')
            {
                result[result_index] = '\0';
				/* printf("%s at %s\n", "CUTOFF INST a new node", temp->buffer + i + 1); */
                *head = instantiate_node(temp->buffer + i + 1);
                free(temp);
                return result;
            }
            i++;
        }
		temp = temp->link;
    }
	free(temp);
	result[result_index] = '\0';
	*head = NULL;
	return result;
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
		temp = temp->link;
	}
	result[len] = '\0';
	free(temp);
	printf("%s\n", result);
	free(result);
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
		append_node(&head, buffer);
		if (ft_strchr(head->buffer, '\n'))
			return (extract_line(&head));
	}
	/* debug_print_full_node(&head); */

	if (head != NULL)
		return(extract_line(&head));
	return NULL;
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

    while (i < 10)
    {
        line = get_next_line(fd);
		if (line != NULL)
		{
			printf("line %d, %s  \n", i, line);
			free(line);
			printf("_______ BREAK _______ \n");
		}
        i++;
    }
    close(fd);

    return 0;
}

