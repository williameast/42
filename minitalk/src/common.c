/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:54:40 by weast             #+#    #+#             */
/*   Updated: 2025/01/27 16:05:32 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/* void transmit_bit(int pid, int bit) */
/* { */
/*     if (bit == 0) */
/*         kill(pid, SIGUSR2); */
/*     else if (bit == 1) */
/* 		kill(pid, SIGUSR1); */
/* 	pause(); */
/* } */

/* void transmit_char(int pid, char c) */
/* { */
/*     int index; */

/*     for (index = 7; index >= 0; index--) */
/*     { */
/*         int bit = (c >> index) & 1; */
/*         transmit_bit(pid, bit); */
/*     } */
/* } */
