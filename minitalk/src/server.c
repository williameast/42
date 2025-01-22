/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:33:57 by weast             #+#    #+#             */
/*   Updated: 2025/01/22 15:01:43 by weast            ###   ########.fr       */
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

// shift bit by 1 on SIGUSR1. if 8 bits recieved, print c otherwise shift char
// bit 1

void	handle_signal(int signal)
{
	static unsigned char	character;
	static int	bit_index;

	if (signal == SIGUSR1)
		character = character | 1;
	if (bit_index++ == 8)
	{
		if (character == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", character);
	bit_index = 0;
	character = 0;
	}
	else
		character = character << 1;
}

int	main(void)
{
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	ft_printf("%i\n", getpid());
	while (1)
		pause();
	return (0);
}
