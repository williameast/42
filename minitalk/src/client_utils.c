/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:21:15 by weast             #+#    #+#             */
/*   Updated: 2025/01/29 15:32:41 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minitalk.h"


static volatile sig_atomic_t ack_received = 0;

// wait for the signal indicator to change before sending next bit
static int transmit_bit(int pid, int bit)
{
	int	timeout_counter = 0;

    if (bit == 0)
        kill(pid, SIGUSR2);
    else if (bit == 1)
        kill(pid, SIGUSR1);
    while (!ack_received)
	{
		if (timeout_counter++ >= TIMEOUT)
		{
			return (-1);
		}
		usleep(50);
	}
    ack_received = 0;
	return (0);
}

static int transmit_char(int pid, char c)
{
    int index;
	int	bit;

    for (index = 7; index >= 0; index--)
    {
        bit = (c >> index) & 1;
        if (transmit_bit(pid, bit) == -1)
			return (-1);
    }
	return (0);
}

int	transmit_message(int pid, char *message)
{
    int i;

    i = 0;
    while (message[i] != '\0')
    {
        if(transmit_char(pid, message[i]) == -1)
			return (-1);
        i++;
    }
    if (transmit_char(pid, '\0') == -1)
		return (-1);
	return (0);
}

void transmit_length(int pid, char *message)
{
    char *len;

    len = ft_itoa(ft_strlen(message));
    if (transmit_message(pid, len) == -1)
	{
		ft_printf("ERROR: server timed out.\n");
		free(len);
		exit(1);
	}
    free(len);
}

void client_signal(int signal, siginfo_t *info, void *context)
{
    (void)context;
    (void)info;

    if (signal == SIGUSR1)
        ack_received = 1;
	else if (signal == SIGUSR2)
	{
		ft_printf("ERROR: Server rejected the message.\n");
		exit(1);
	}
}
