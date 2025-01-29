/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:14:00 by weast             #+#    #+#             */
/*   Updated: 2025/01/29 11:39:01 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"


static volatile sig_atomic_t g_ack_received = 0;

void transmit_bit(int pid, int bit)
{
    if (bit == 0)
        kill(pid, SIGUSR2);
    else if (bit == 1)
        kill(pid, SIGUSR1);

    // Wait for acknowledgment before sending next bit
    while (!g_ack_received)
        usleep(100);
    g_ack_received = 0;
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

void transmit_length(int pid, char *message)
{
    char *len;

    len = ft_itoa(ft_strlen(message));
    transmit_message(pid, len);
    free(len);
}

void handle_signal(int signal, siginfo_t *info, void *context)
{
    (void)context;
    (void)info;

    if (signal == SIGUSR1)
    {
        g_ack_received = 1;
        if (DEBUG)
            ft_printf("Received acknowledgment from server\n");
    }
}

int main(int argc, char **argv)
{
    pid_t server_pid;
    char *message;
    struct sigaction sa;

    if (argc != 3)
    {
        ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
    }
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        ft_printf("Failed to set up signal handler\n");
        return (1);
    }

    server_pid = ft_atoi(argv[1]);
    message = argv[2];

    if (DEBUG)
    {
        ft_printf("Client PID: %d\n", getpid());
        ft_printf("Sending message to server PID: %d\n", server_pid);
    }
    transmit_length(server_pid, message);
    transmit_message(server_pid, message);
    ft_printf("Message transmission completed\n");
    usleep(1000);

    return (0);
}
