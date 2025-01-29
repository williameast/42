/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:09:38 by weast             #+#    #+#             */
/*   Updated: 2025/01/29 15:28:38 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINITALK_H
# define MINITALK_H


# define DEBUG 1
# define LENGTH_BUFFER_SIZE 10
# define MAX_MESSAGE_LENGTH 9999999
# define TIMEOUT 10000

/* internal includes */
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# include <unistd.h>
# include <signal.h>


typedef struct s_client {
    pid_t client_pid;                     // PID of the client
    unsigned char current_char;           // Current character being received (8 bits)
    int bit_index;                        // Index of the bit being processed (0-7)
    int message_length;                   // Length of the incoming message
    int metadata_received;                // Flag to indicate if metadata (length) has been fully received
    int length_index;                     // Index for writing into the length_buffer
    char length_buffer[LENGTH_BUFFER_SIZE]; // Fixed-size buffer for the message length
    char *message_buffer;                 // Dynamically allocated buffer for the message content
} t_client;


int	create_message_buffer(t_client *client);
void	initialize_client(t_client *client);
void	print_output(t_client *client);


int	transmit_message(int pid, char *message);
void transmit_length(int pid, char *message);
void client_signal(int signal, siginfo_t *info, void *context);
/* declarations */
/* declarations end */

#endif // MINITALK_H
