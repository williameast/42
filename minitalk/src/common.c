/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:54:40 by weast             #+#    #+#             */
/*   Updated: 2025/01/22 14:15:19 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

// send a signal from MSB to LSB to PID
int transmit_bit(int pid, unsigned char byte)
{
    int i;

    i = 8;
    while (i > 0)
    {
        i--; // Start from the MSB, which is 7
        if ((byte >> i) & 1) // Extract the i-th bit
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100); // Delay to ensure the receiver can process the signal
    }
    return (1);
}

int transmit_string(int pid, char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!transmit_bit(pid, str[i++]))
        {
            ft_printf("ERROR: Failed to transmit character: <%c>\n", str[i - 1]);
            return (0);
        }
    }
    if (!transmit_bit(pid, '\0'))
    {
        ft_printf("ERROR: Failed to transmit null terminator\n");
        return (0);
    }
    return (1);
}
