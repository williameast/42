/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:07:12 by William           #+#    #+#             */
/*   Updated: 2024/12/16 17:14:42 by William          ###   ########.fr       */
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
static int	count_words(const char *str, char delimiter)
{
	size_t	i = 0;
	size_t	wordcount = 0;
	size_t delimiter_count;

	if (!str)
		return (0);

	while (str[i] != '\0')
	{
		if (str[i] != delimiter)
		{
			wordcount++;
			while (str[i] != '\0' && str[i] != delimiter)
				i++;
		}
		else
		{
			delimiter_count = 0;
			while (str[i] == delimiter)
			{
				delimiter_count++;
				i++;
			}
			wordcount += (delimiter_count + 2) / 3;
		}
	}
	return (wordcount);
}
static int	get_word_length(const char *s, unsigned int start, char c)
{
	int	i;

	i = start;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i - start);
}

static char **free_layered(char **arr, int j)
{
    while (j > 0)
        free(arr[--j]);
    free(arr);
    return (NULL);
}

char **ft_split_strict(const char *s, char c)
{
    char    **arr;
    size_t  i = 0;
    int     j = 0;

    // Allocate memory for the array of strings
    arr = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
    if (!arr)
        return (NULL);

    while (s[i] != '\0')
    {
        // Handle words (non-delimiter characters)
        if (s[i] != c)
        {
            arr[j++] = ft_substr(s, i, get_word_length(s, i, c));
            if (!arr[j - 1])
                return (free_layered(arr, j - 1)); // Return NULL on failure
            i += get_word_length(s, i, c);
        }
        // Handle groups of delimiters (3 or more consecutive)
        else
        {
            size_t delimiter_count = 0;
            while (s[i] == c)
            {
                delimiter_count++;
                i++;
            }
            if (delimiter_count >= 3)
            {
                size_t empty_count = (delimiter_count + 2 ) / 3; // Number of empty strings to create
                for (size_t k = 0; k < empty_count; k++)
                {
                    arr[j++] = ft_strdup(""); // Allocate empty string
                    if (!arr[j - 1])
                        return (free_layered(arr, j - 1)); // Return NULL on failure
                }
            }
        }
    }
    arr[j] = NULL; // Null-terminate the array
    return (arr);
}
