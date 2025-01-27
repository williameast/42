/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:13:46 by weast             #+#    #+#             */
/*   Updated: 2025/01/27 17:38:19 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"


void initialize_client(t_client *client)
{
    client->client_pid = 0;
    client->current_char = 0;
    client->bit_index = 0;
    client->message_length = 0;
    client->metadata_received = 0;
    client->length_index = 0;
    client->message_buffer = NULL;

    // Initialize the length_buffer with 0s
    for (int i = 0; i < LENGTH_BUFFER_SIZE; i++)
        client->length_buffer[i] = 0;
}

int process_metadata(int signal, t_client *state)
{
    if (signal == SIGUSR1)
        state->current_char |= 1;  // Set LSB to 1
    state->bit_index++;

    if (state->bit_index == 8)  // After receiving 1 byte (8 bits)
    {
        if (state->current_char == '\0')  // Null terminator indicates end of length string
        {
            // Convert the length string to an integer (with boundary check)
            state->message_length = ft_atoi(state->length_buffer);
            if (state->message_length > MAX_MESSAGE_LENGTH)
            {
                // Handle the case where the message length exceeds the limit
                ft_printf("Message length exceeds maximum allowed value.\n");
                return -1;  // Error case
            }

            // Allocate buffer for the message content
            state->message_buffer = (char *)malloc(state->message_length + 1);
            if (state->message_buffer == NULL)
                return -1;  // Error handling if allocation fails

            state->length_index = 0;
			state->message_buffer[state->message_length + 1] = '\0';
            state->metadata_received = 1;
        }
        else
        {
            // Store the byte in the length_buffer for conversion
            state->length_buffer[state->length_index] = state->current_char;
            state->length_index++;
        }

        // Reset for next byte
        state->current_char = 0;
        state->bit_index = 0;
    }
    else
    {
        state->current_char <<= 1;  // Shift left to prepare for next bit
    }

    return 0;
}

void	print_output(t_client *state)
{
	ft_printf("%s\n", state->message_buffer);
	free(state->message_buffer);  // Free the message buffer after use
	state->message_buffer = NULL;
	state->metadata_received = 0;  // Reset for next client
}


void process_bit(int signal, t_client *state)
{
    if (!state->metadata_received)
    {
        if (process_metadata(signal, state) == -1)
            return;  // Exit if there's an error processing metadata
    }
    else
    {
        if (signal == SIGUSR1)
            state->current_char |= 1;  // Set LSB to 1
        state->bit_index++;
        if (state->bit_index == 8)  // After receiving 1 byte
        {
            if (state->current_char == '\0')  // Null terminator indicates end of message
				print_output(state);
            else
                state->message_buffer[state->length_index++] = state->current_char;
            state->current_char = 0;
            state->bit_index = 0;
        }
        else
            state->current_char <<= 1;  // Shift left for next bit
    }
}
// Signal handler function
void handle_signal(int signal, siginfo_t *info, void *context)
{
    static t_client client = {0};  // Initialize client structure
    pid_t sender_pid;

    (void)context;  // Unused parameter
    sender_pid = info->si_pid;

    if (client.client_pid != sender_pid)
    {
		initialize_client(&client);
		client.client_pid = sender_pid;
        if (DEBUG)
            ft_printf("New client connected: PID: %d\n", sender_pid);
    }

    // Process the bit (handles both metadata and actual message)
    process_bit(signal, &client);
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
