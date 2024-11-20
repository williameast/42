/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:43:06 by William           #+#    #+#             */
/*   Updated: 2024/08/19 15:04:53 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line_utils.c"

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
    t_node	*current_node;

    new_node = instantiate_node(data);

    if (*head == NULL)
        *head = new_node;
    else
    {
        current_node = *head;
        while (current_node->link != NULL)
            current_node = current_node->link;
    current_node->link = new_node;
    }
}
void	print_string(t_node *head)
{
    t_node *current_node;
    int	strlen;
    char	*result;
    /* int	i; */

    /* i = 0; */
    strlen = 0;
    current_node = head;
    while(current_node != NULL)
    {
        strlen += ft_strlen(current_node->buffer);
        current_node = current_node->link;
    }
    result = malloc(strlen + 1); //remember to check allocation was success!
    if (result == NULL)
        return;
    result[0] = '\0';
    current_node = head;
    while(current_node != NULL)
    {
        ft_strlcat(result, current_node->buffer, strlen + 1);
        current_node = current_node->link;
    }
    printf("%s\n", result);
    free(result);
}
void get_next_line(int fd)
{
    static t_node *head = NULL;  // Maintain the linked list between calls
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    char *newline_pos;
    t_node *current_node;

    // Keep reading until we find a newline or reach EOF
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer
        append_node(&head, buffer);  // Append the entire buffer to the linked list

        // Check if there's a newline in the current linked list content
        current_node = head;
        while (current_node != NULL)
        {
            newline_pos = ft_strchr(current_node->buffer, '\n');
            if (newline_pos != NULL)
            {
                *newline_pos = '\0';  // Terminate at the newline
                print_string(head);  // Print the current content up to the newline

                // Move the remaining content after the newline to the start of the buffer
                char *remaining = strdup(newline_pos + 1);

                // Free the current linked list
                t_node *tmp;
                while (head != NULL)
                {
                    tmp = head;
                    head = head->link;
                    free(tmp);
                }

                // Add the remaining content as the new head of the list
                if (remaining && *remaining != '\0')
                    append_node(&head, remaining);
                free(remaining);

                return;
            }
            current_node = current_node->link;
        }
    }

    // If EOF is reached and no newline was found, print what's left
    if (bytes_read == 0 && head != NULL)
    {
        print_string(head);

        // Free the linked list
        t_node *tmp;
        while (head != NULL)
        {
            tmp = head;
            head = head->link;
            free(tmp);
        }
    }
}


int main(void) {
	int	fd;
    int	i = 0;

	char *filename = "test.txt";

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("%s could not be found.", filename));

    while (i < 10)
    {
        get_next_line(fd);
        printf("_______ BREAK _______ \n");
        i++;
    }
    close(fd);

    return 0;
}
