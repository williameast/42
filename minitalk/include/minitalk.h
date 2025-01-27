/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:09:38 by weast             #+#    #+#             */
/*   Updated: 2025/01/27 16:34:22 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINITALK_H
# define MINITALK_H


# define DEBUG 1



/* internal includes */
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include <unistd.h>
# include <signal.h>


typedef struct s_client
{
    pid_t client_pid;
    unsigned char current_char;
    int bit_index;
} t_client;



/* declarations */
/* declarations end */

#endif // MINITALK_H
