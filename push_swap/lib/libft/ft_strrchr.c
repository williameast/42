/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:34:59 by weast             #+#    #+#             */
/*   Updated: 2024/07/01 12:33:01 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*temp;

	temp = NULL;
	while (*str)
	{
		if (*str == (char)c)
			temp = (char *)str;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (temp);
}
