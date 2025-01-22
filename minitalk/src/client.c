/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:14:00 by weast             #+#    #+#             */
/*   Updated: 2025/01/22 15:06:06 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/* static unsigned char current_byte = 0; */
/* static int bit_position = 0; */
/* static char message[1024]; */
/* static int message_index = 0; */

/* void signal_handler(int sig) */
/* { */
/*     // Update the current bit based on the received signal */
/*     if (sig == SIGUSR1) */
/*         current_byte |= (1 << (7 - bit_position)); // Set the bit to 1 */

/*     bit_position++; */

/*     // If a full byte is received */
/*     if (bit_position == 8) */
/*     { */
/*         if (current_byte == '\0') // End of message */
/*         { */
/*             message[message_index] = '\0'; // Null-terminate the message */
/*             ft_printf("Received message: %s\n", message); */
/*             message_index = 0; // Reset for the next message */
/*         } */
/*         else if (message_index < 1024 - 1) */
/*         { */
/*             message[message_index++] = current_byte; // Store the byte */
/*         } */
/*         else */
/*         { */
/*             ft_printf("Error: Message too long!\n"); */
/*         } */

/*         // Reset for the next byte */
/*         current_byte = 0; */
/*         bit_position = 0; */
/*     } */
/* } */



/* void decode_signal(const char *received_bits) */
/* { */
/*     int i = 0; */
/*     char current_char = 0; */

/*     ft_printf("Decoded string: "); */
/*     while (received_bits[i] != '\0') */
/*     { */
/*         current_char = (current_char << 1) | (received_bits[i] - '0'); */
/*         if ((i + 1) % 8 == 0) // Every 8 bits form a character */
/*         { */
/*             if (current_char == '\0') // Null terminator indicates end of string */
/*                 break; */
/*             ft_printf("%c", current_char); */
/*             current_char = 0; // Reset for the next character */
/*         } */
/*         i++; */
/*     } */
/*     ft_printf("\n"); */
/* } */

/* int main(void) */
/* { */
/*     // Setup signal handlers for SIGUSR1 and SIGUSR2 */

/*     // Print PID for the sender */
/*     ft_printf("Receiver PID: %d\n", getpid()); */
/*     ft_printf("Waiting for signals...\n"); */

/*     // Keep the program running to receive signals */
/*     while (1) */
/*     { */
/*         pause(); // Wait for a signal */
/*     } */

/*     return 0; */
/* } */


int main(int argc, char *argv[])
{
	int	pid;
	if (argc != 3)
	{
		ft_printf("usage: ./client <pid> <str>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	transmit_string(pid, argv[2]);
    return 0;
}
