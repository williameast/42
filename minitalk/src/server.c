/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:46 by weast             #+#    #+#             */
/*   Updated: 2025/01/29 11:38:00 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"


void initialize_client(t_client *client)
{
    int	i;

    i = 0;
    client->client_pid = 0;
    client->current_char = 0;
    client->bit_index = 0;
    client->message_length = 0;
    client->metadata_received = 0;
    client->length_index = 0;
    client->message_buffer = NULL;
    while (i < LENGTH_BUFFER_SIZE)
        client->length_buffer[i++] = 0;
}

int process_metadata(int signal, t_client *client)
{
    if (signal == SIGUSR1)
        client->current_char |= 1;
    client->bit_index++;
    if (client->bit_index == 8)
    {
        if (client->current_char == '\0')
        {
            client->message_length = ft_atoi(client->length_buffer);
            if (client->message_length > MAX_MESSAGE_LENGTH)
            {
                ft_printf("Message length exceeds maximum allowed value.\n");
                if (client->message_buffer)
                        free(client->message_buffer);
                client->message_buffer = NULL;
                return -1;
            }
            client->message_buffer = (char *)malloc(client->message_length + 1);
            if (client->message_buffer == NULL)
                return -1;
            client->length_index = 0;
			client->message_buffer[client->message_length] = '\0';
            client->metadata_received = 1;
        }
        else
        {
            client->length_buffer[client->length_index] = client->current_char;
            client->length_index++;
        }
        client->current_char = 0;
        client->bit_index = 0;
    }
    else
        client->current_char <<= 1;  // Shift left to prepare for next bit
    return 0;
}

void	print_output(t_client *client)
{
	ft_printf("%s\n", client->message_buffer);
	free(client->message_buffer);  // Free the message buffer after use
	client->message_buffer = NULL;
	client->metadata_received = 0;  // Reset for next client
}

void process_bit(int signal, t_client *client)
{
    if (!client->metadata_received)
    {
        if (process_metadata(signal, client) == -1)
            return;
    }
    else
    {
        if (signal == SIGUSR1)
            client->current_char |= 1;
        client->bit_index++;

        if (client->bit_index == 8)
        {
            if (client->current_char == '\0')
                print_output(client);
            else
                client->message_buffer[client->length_index++] = client->current_char;
            client->current_char = 0;
            client->bit_index = 0;
        }
        else
            client->current_char <<= 1;
    }
}

void handle_signal(int signal, siginfo_t *info, void *context)
{
    static t_client client = {0};
    pid_t sender_pid;

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

int main(void)
{
    struct sigaction sa;

    ft_printf("%d\n", getpid());  // Print the server PID for the client to connect
	sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause();  // Wait for signals

    return 0;
}
