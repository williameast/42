/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:07:12 by William           #+#    #+#             */
/*   Updated: 2024/12/12 13:18:00 by William          ###   ########.fr       */
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

    if (!ptr) // If the pointer is NULL, behave like malloc
        return (malloc(new_size));
    if (new_size == 0) // If new size is 0, free the pointer and return NULL
    {
        free(ptr);
        return (NULL);
    }
    new_ptr = malloc(new_size); // Allocate new memory
    if (!new_ptr)
        return (NULL);
    ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    free(ptr); // Free the old memory block
    return (new_ptr);
}
