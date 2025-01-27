/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:33:57 by weast             #+#    #+#             */
/*   Updated: 2025/01/27 16:28:29 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:46 by weast             #+#    #+#             */
/*   Updated: 2025/01/22 13:33:54 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	handle_new_client(pid_t sender_pid, t_client *state)
{
	state->client_pid = sender_pid;
	state->current_char = 0;
	state->bit_index = 0;
	if (DEBUG)
		ft_printf("new client connected: PID: %i\n", state->client_pid);
}

// if sig1 is caught, set LSB to 1
// current char = 0000 0000, then it becomes 1000 0000?
void	process_bit(int signal, t_client *state)
{
	if (signal == SIGUSR1)
        state->current_char |= 1;
	state->bit_index++;
	if (state->bit_index == 8)
	{
		if (state->current_char == '\0')
		{
			ft_printf("\n");
			return ;
		}
		else
			ft_printf("%c", state->current_char);
	state->current_char = 0;
	state->bit_index = 0;
	}
	else
		state->current_char <<= 1;
}

// Signal handler function
void handle_signal(int signal, siginfo_t *info, void *context)
{
    static t_client client = {0, 0, 0};
	pid_t sender_pid;

    (void)context;
    sender_pid = info->si_pid;
    if (client.client_pid != sender_pid)
        handle_new_client(sender_pid, &client);
    process_bit(signal, &client);
}

int main(void)
{
    struct sigaction sa;

	ft_printf("%d\n", getpid());
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause();

    return 0;
}
