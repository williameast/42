/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:15:03 by William           #+#    #+#             */
/*   Updated: 2024/08/27 23:32:58 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_node
{
	char			*data;
	struct s_node	*link;
}				t_node;

int		ft_strlen(const char *str);
void	free_lst(t_node *lst);
char	*get_next_line(int fd);
int		check_for_newline(t_node *lst);
t_node	*get_tail(t_node *lst);
void	read_and_save(int fd, t_node **lst);
void	add_to_lst(t_node **lst, char *buf, int readed);
void	extract_line(t_node *lst, char **line);
void	generate_line(char **line, t_node *lst);
void	extract_remainder_and_free(t_node **lst);
#endif
