/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:59:15 by weast             #+#    #+#             */
/*   Updated: 2024/11/26 17:07:50 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int read_something(void)
{
  int    fd;
  char  *next_line;
  int  count;

  count = 0;
  fd = open("example.txt", O_RDONLY);
  while (1)
  {
    next_line = get_next_line(fd);
    if (next_line == NULL)
        break ;
    count++;
    ft_printf("we here");
    ft_printf("[%d]:%s\n", count, next_line);
    next_line = NULL;
  }
  close(fd);
  return (0);
}
