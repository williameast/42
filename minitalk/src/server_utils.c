/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:36:47 by weast             #+#    #+#             */
/*   Updated: 2025/01/29 15:48:50 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	initialize_client(t_client *client)
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

int	create_message_buffer(t_client *client)
{
	client->message_length = ft_atoi(client->length_buffer);
	if (client->message_length > MAX_MESSAGE_LENGTH)
	{
		ft_printf("ERROR: Message length exceeds maximum allowed value.\n");
		if (client->message_buffer)
			free(client->message_buffer);
		client->message_buffer = NULL;
		return (-1);
	}
	client->message_buffer = (char *)malloc(client->message_length + 1);
	if (client->message_buffer == NULL)
	{
		ft_printf("ERROR: Failed to allocate message buffer.\n");
		return (-1);
	}
	client->length_index = 0;
	client->message_buffer[client->message_length] = '\0';
	client->metadata_received = 1;
	return (0);
}

void	print_output(t_client *client)
{
	ft_printf("%s\n", client->message_buffer);
	free(client->message_buffer);
	client->message_buffer = NULL;
	client->metadata_received = 0;
}
