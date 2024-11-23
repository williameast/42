/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:07:35 by weast             #+#    #+#             */
/*   Updated: 2024/07/01 13:46:03 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*new_str;
	unsigned int		str_len;
	int					new_len;

	str_len = ft_strlen(s);
	new_len = len;
	if (str_len <= start || !str_len || !len)
		return (ft_strdup(""));
	if (len > str_len - start)
		new_len = str_len - start;
	new_str = (char *)malloc(new_len + 1);
	if (new_str)
		ft_strlcpy(new_str, s + start, new_len + 1);
	return (new_str);
}
