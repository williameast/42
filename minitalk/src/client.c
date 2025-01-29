/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:14:00 by weast             #+#    #+#             */
/*   Updated: 2025/01/29 15:29:08 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"


int main(int argc, char **argv)
{
    struct sigaction sa;
    pid_t server_pid;
    char *message;

    if (argc != 3)
    {
        ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
    }
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = client_signal;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        ft_printf("Failed to set up signal handler\n");
        return (1);
    }
    server_pid = ft_atoi(argv[1]);
    message = argv[2];
    transmit_length(server_pid, message);
    transmit_message(server_pid, message);
    ft_printf("Message transmission completed\n");
    return (0);
}
