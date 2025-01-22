/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:09:38 by weast             #+#    #+#             */
/*   Updated: 2025/01/22 14:11:24 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINITALK_H
# define MINITALK_H



/* internal includes */
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include <unistd.h>
# include <signal.h>



/* declarations */
/* Declarations from server.c */

/* Declarations from client.c */

/* Declarations from common.c */
int	transmit_bit(int pid, unsigned char bit);
int	transmit_string(int pid, char *str);

/* declarations end */

#endif // MINITALK_H
