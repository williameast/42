/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:34:42 by weast             #+#    #+#             */
/*   Updated: 2024/08/20 13:31:44 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>


# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif


typedef struct s_node
{
    	char	buffer[BUFFER_SIZE + 1];
    	struct	s_node	*link;
        int	nl_pos;
}	t_node;


#endif // GET_NEXT_LINE_H