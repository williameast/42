/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:11:47 by William           #+#    #+#             */
/*   Updated: 2024/08/15 12:55:09 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include "get_next_line_utils.c"
#include <stdio.h>

// this uses a dirty hack to avoid having to use strcpy.
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

char	*get_full_string(t_node *head)
{
    t_node *current_node;
    int	strlen;
    char	*result;

    strlen = 0;
    current_node = head;
    while(current_node != NULL)
    {
        strlen += ft_strlen(current_node->buffer);
        current_node = current_node->link;
    }
    result = malloc(strlen + 1); //remember to check allocation was success!
    if (result == NULL)
        return (NULL);
    result[0] = '\0';
    current_node = head;
    while(current_node != NULL)
    {
        ft_strlcat(result, current_node->buffer, strlen + 1);
        current_node = current_node->link;
    }
    return (result);
}
// Function to free the linked list
void free_linked_list(t_node **head)
{
    t_node *tmp;

    while (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->link;
        free(tmp);
    }
}

// Function to process the newline when found
void process_newline(t_node **head, char *newline_pos)
{
    char remainder[BUFFER_SIZE + 1];
    *newline_pos = '\0';  // Terminate at the newline
    get_full_string(*head);  // Print the current content up to the newline
    // Allocate a new buffer to store the remaining content after the newline
    remainder[0] = '\0';

    // Copy the remaining content after the newline to the new buffer
    ft_strlcat(remainder, newline_pos + 1, sizeof(remainder));

    // Free the current linked list
    free_linked_list(head);

    // Add the remaining content as the new head of the list
    if (*remainder != '\0')
        append_node(head, remainder);
}

// Function to search for a newline in the linked list
int find_and_process_newline(t_node **head)
{
    t_node *current_node = *head;
    char *newline_pos;

    while (current_node != NULL)
    {
        newline_pos = ft_strchr(current_node->buffer, '\n');
        if (newline_pos != NULL)
        {
            process_newline(head, newline_pos);
            return 1;  // Newline found and processed
        }
        current_node = current_node->link;
    }
    return 0;  // No newline found
}

// Main function to get the next line from the file
void get_next_line(int fd)
{
    static t_node *head = NULL;  // Maintain the linked list between calls
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;

    if (head != NULL && find_and_process_newline(&head))
        return;  // Exit the function after printing one line
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer
        append_node(&head, buffer);  // Append the entire buffer to the linked list
        if (find_and_process_newline(&head))
            return;  // Exit the function after printing one line
    }
    if (bytes_read == 0 && head != NULL)
    {
        get_full_string(head);
        free_linked_list(&head);  // Free the linked list
    }
}
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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

/* int main() { */
/*     t_node *head; */
/*     /\* t_node *current_node; *\/ */

/*     head = NULL; */
/*     char *test_buf = "this is a test string! I have many things to sa"; */
/*     char *test_buf2 = "another piece of info."; */
/*     char *test_buf3 = "I love the noise\n Df farts."; */
/*     char *test_buf4 = "how do you do!."; */

/*     append_node(&head, test_buf); */
/*     append_node(&head, test_buf2); */
/*     append_node(&head, test_buf3); */
/*     append_node(&head, test_buf4); */
/*     /\* current_node = head; *\/ */
/*     /\* while(current_node != NULL) *\/ */
/*     /\* { *\/ */
/*     /\*     printf("%s\n", current_node->buffer); *\/ */
/*     /\*     current_node = current_node->link; *\/ */
/*     /\* } *\/ */

/*     get_full_string(head); */

/*     return 0; */
/* } */

/* void	append_output_string(t_node *head, char *str) */
/* { */
/*     // str buffer should be calculated beforehand. */
/*     // cant you just get the strlen of the last buffer? */

/*     int	strlen; */
/*     char	*result; */

/*     strlen = 0; */
/*     while(head != NULL) */
/*     { */
/*         strlen += ft_strlen(head->buffer); */
/*         head = head->link; */
/*     } */

/*     result = malloc(strlen + 1); //remember to check allocation was success! */
/*     result[0] = '\0'; */

/*     while(head != NULL) */
/*     { */
/*         strlen += ft_strlen(head->buffer); */
/*         head = head->link; */
/*     } */



/* } */

