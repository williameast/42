/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:08:28 by William           #+#    #+#             */
/*   Updated: 2024/09/05 12:25:39 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int	check_for_nl(t_lst **list)
{
	t_lst	*temp;
	int	len;

	len = 0;
	if (!(*list))
	{
		/* printf("%s\n", "CHECK_FOR_NL: list does not exist, returning -1"); */
		return (-1);
	}
	temp = *list;
	while(temp != NULL)
	{
		if (temp->nl_pos)
		{
			len += (ft_strlen(temp->buffer) - ft_strlen(temp->nl_pos));
			/* printf("CHECK_FOR_NL: exiting function with a length of <%i>\n", len); */
			if (len > 0)
				return (len + 1);
			else
				return (1);
		}
		else
			len += ft_strlen(temp->buffer);
		temp = temp->link;
	}
	if (len > 0)
		return (-len);
	else
		return (-1);
}

char	*generate_line(t_lst **list)
{
	char	*line;
	t_lst	*temp;
	int	len;

	len = check_for_nl(list);
	if (len < 0)
		len = len * -1;
	line = (char *)malloc(sizeof(char) * len);
	if (!line || !(*list))
		return (NULL);
	line[0] = '\0';
	temp = *list;
	while (temp != NULL)
	{
		if (temp->nl_pos == NULL)
			line = ft_strjoin(line, temp->buffer);
		else
		{
			temp->buffer[ft_strlen(temp->buffer) - ft_strlen(temp->nl_pos) + 1] = '\0';
			/* printf("GENERATE_LINE: temp->buffer: <%s>\n", temp->buffer); */
			line =ft_strjoin(line, temp->buffer);
		}
		temp = temp->link;
	}
	/* printf("%s <%s>\n", "GENERATE LINE: I have generated this line!", line); */
	return (line);
}

char	*get_remainder(t_lst **list)
{
	t_lst	*temp;

	temp = *list;
	while (temp->nl_pos == NULL)
		temp = temp->link;
	return (temp->nl_pos + 1);
}

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	char	*remainder;
	static t_lst *list;
	int	bytes_read;

	while (check_for_nl(&list) < 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return(generate_line(&list)); // to make sure that we break if there is nothing being read in, then just dump.
		buffer[bytes_read] = '\0';
		add_node(&list, buffer);
	}
	line = generate_line(&list);
	if (check_for_nl(&list))
	{
		remainder = get_remainder(&list);
		free_list(&list);
		add_node(&list, remainder); // add the remainder from the nl breakpoint
	}
	else
		free_list(&list);
	return (line); // change back to NULL
}

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

    while (i < 6)
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
