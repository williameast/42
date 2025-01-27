/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:14:00 by weast             #+#    #+#             */
/*   Updated: 2025/01/27 16:36:54 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"


void transmit_bit(int pid, int bit)
{
    if (bit == 0)
        kill(pid, SIGUSR2);
    else if (bit == 1)
		kill(pid, SIGUSR1);
	usleep(500);
}

void transmit_char(int pid, char c)
{
    int index;

    for (index = 7; index >= 0; index--)
    {
        int bit = (c >> index) & 1;
        transmit_bit(pid, bit);
    }
}

// first, send the length of the string.
// then send null termiinator, indicating the beginning of the message
// then send the message
// then final null terminator
void transmit_message(int pid, char *message)
{
    int i;

	i = 0;
    while (message[i] != '\0')
    {
        transmit_char(pid, message[i]);
        i++;
    }
    transmit_char(pid, '\0');
}

int main(int argc, char **argv)
{
	pid_t server_pid;
	char *message;

    if (argc != 3)
    {
        ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
    }

    server_pid = ft_atoi(argv[1]);
    message = argv[2];

	if (DEBUG)
    {
		ft_printf("Client PID: %d\n", getpid());
		ft_printf("Sending message to server PID: %d\n", server_pid);
	}
    transmit_message(server_pid, message);
	ft_printf("finished transmitting message");

    return (0);
}
