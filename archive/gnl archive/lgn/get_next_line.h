/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:48:57 by William           #+#    #+#             */
/*   Updated: 2024/09/05 12:33:20 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> //remove this!!
# include <fcntl.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
# endif


typedef struct s_lst
{
    	char	*buffer;
        char	*nl_pos;
    	struct	s_lst	*link;
}	t_lst;



int	ft_strlen(char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
void	add_node(t_lst **list ,char *data);
void	free_list(t_lst **list);

int	check_for_nl(t_lst **list);
char	*generate_line(t_lst **list);
char	*get_remainder(t_lst **list);
char	*get_next_line(int fd);

#endif
