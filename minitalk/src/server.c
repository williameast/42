/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:46 by weast             #+#    #+#             */
/*   Updated: 2025/01/29 15:47:59 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	process_metadata(int signal, t_client *cli)
{
	if (signal == SIGUSR1)
		cli->current_char |= 1;
	cli->bit_index++;
	if (cli->bit_index == 8)
	{
		if (cli->current_char == '\0')
		{
			if (create_message_buffer(cli) != 0)
			{
				kill(cli->client_pid, SIGUSR2);
				return (-1);
			}
		}
		else
			cli->length_buffer[cli->length_index++] = cli->current_char;
		cli->current_char = 0;
		cli->bit_index = 0;
	}
	else
		cli->current_char <<= 1;
	return (0);
}

void	process_bit(int signal, t_client *cli)
{
	if (!cli->metadata_received)
	{
		if (process_metadata(signal, cli) == -1)
			return ;
	}
	else
	{
		if (signal == SIGUSR1)
			cli->current_char |= 1;
		cli->bit_index++;
		if (cli->bit_index == 8)
		{
			if (cli->current_char == '\0')
				print_output(cli);
			else
				cli->message_buffer[cli->length_index++] = cli->current_char;
			cli->current_char = 0;
			cli->bit_index = 0;
		}
		else
			cli->current_char <<= 1;
	}
}

void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static t_client	client = {0};
	pid_t			sender_pid;

	(void)context;
	sender_pid = info->si_pid;
	if (client.client_pid != sender_pid)
	{
		initialize_client(&client);
		client.client_pid = sender_pid;
		if (DEBUG)
			ft_printf("New client connected: PID: %d\n", sender_pid);
	}
	process_bit(signal, &client);
	if (kill(client.client_pid, SIGUSR1) == -1)
		ft_printf("Failed to send acknowledgment to client\n");
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
