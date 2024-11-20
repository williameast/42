/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:38:06 by William           #+#    #+#             */
/*   Updated: 2024/08/19 14:58:10 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"
#include <stdio.h>

// create a new node item. (probably should go in utils.)

t_node *instantiate_node(const char *data)
{
	t_node	*new_node;
	char	*newline_ptr;

	new_node = (t_node *)malloc((sizeof(t_node)));
	if (new_node == NULL)
		return (NULL);
	ft_strcpy(new_node->buffer, data);
	newline_ptr = ft_strchr(new_node->buffer, '\n');
	if (newline_ptr != NULL)
	{
		new_node->newline_position = newline_ptr - new_node->buffer;
		new_node->has_newline = 1;
	}
	else
	{
		new_node->newline_position = -1;
		new_node->has_newline = 0;
	}
	new_node->link = NULL;
	return (new_node);
}
// in this function, we use a pointer to the pointer of head#
// so that when we traverse the list, we are not actually losing the
// pointer to the head of the list. instead we create a "copy" to traverse
// to the end of the list, and then attach the node there.
void	append_node(t_node **head, const char *data)
{
	t_node	*new_node;
	t_node	*temp_node;

	new_node = instantiate_node(data);

	if (*head == NULL)
		*head = new_node;

	else
	{
		temp_node = *head;
		while (temp_node->link != NULL)
			temp_node = temp_node->link;
		temp_node->link = new_node;
	}
}

int	get_line_len(t_node **head)
{
	t_node *temp;
	int	len;

	temp = *head;
	len = 0;
	while (temp->link != NULL)
	{
		if (temp->has_newline)
		{
			len += temp->newline_position + 1;
			return (len);
		}
		len += ft_strlen(temp->buffer);
		temp = temp->link;
	}
	return (len);
}

char *extract_line(t_node **head) {
    t_node *temp;
    t_node *remainder;
    char *line;
    int line_len;

    line_len = get_line_len(head);
    line = malloc(line_len + 1);  // Allocate memory for the line
    if (line == NULL)
        return (NULL);  // Return NULL if allocation fails

    line[0] = '\0';  // Initialize the line as an empty string
    temp = *head;

    while (temp != NULL) {
        // Check if the current buffer contains a newline
        if (temp->has_newline) {
            // Copy up to and including the newline character
            ft_strlcat(line, temp->buffer, line_len + 1);

            // Create a new node for the remainder after the newline
            remainder = instantiate_node(temp->buffer + temp->newline_position + 1);
            *head = remainder;  // Update the head to point to the remainder

            free(temp);  // Free the old node
            return (line);  // Return the constructed line
        } else {
            // Copy the entire buffer if no newline is found
            ft_strlcat(line, temp->buffer, line_len + 1);

            *head = temp->link;  // Move head to the next node
            free(temp);  // Free the current node
            temp = *head;  // Move to the next node
        }
    }

    return (line);  // Return the final line
}


char *get_next_line(int fd)
{
	static	t_node *head = NULL;
	char buffer[BUFFER_SIZE + 1];
	int	bytes_read;

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		append_node(&head, buffer);

		if (head->has_newline)
			return(extract_line(&head));
	}
	if (head != NULL)
		return extract_line(&head);
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
		printf("line %d, %s  \n", i, line);
		free(line);
        printf("_______ BREAK _______ \n");
        i++;
    }
    close(fd);

    return 0;
}
