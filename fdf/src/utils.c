/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:07:12 by William           #+#    #+#             */
/*   Updated: 2025/01/12 15:37:39 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fdf.h"


int	check_extension(char *filename, char *ext)
{
  int	ext_len;
  int	name_len;

  ext_len = ft_strlen(ext);
  name_len = ft_strlen(filename);
  if (ext_len >= name_len)
    return (0);
  return(!ft_strncmp(ext, &filename[name_len - ext_len], 5));
}

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_int_array(int *array)
{
	if (!array)
		return;
	free(array);
}

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (!ptr)
        return (malloc(new_size));
    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    free(ptr);
    return (new_ptr);
}

