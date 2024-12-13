/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:59:15 by weast             #+#    #+#             */
/*   Updated: 2024/12/04 16:14:06 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int read_something(void)
{
  int    fd;
  char  *next_line;
  int  count;

  count = 0;
  fd = open("maps/4line.fdf", O_RDONLY);
  while (1)
  {
    next_line = get_next_line(fd);
    if (next_line == NULL)
        break ;
    count++;
    ft_printf("[%d]:%s\n", count, next_line);
    next_line = NULL;
  }
  close(fd);
  return (0);
}

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

int	split_array_len(char **arr)
{
	int	i;
	i = 0;

	while (arr[i] != NULL)
		i++;
	return (i);
}

t_crd  *convert_line_into_crds(char *line, int y, int *length)
{
    char    **table;
    t_crd   *out;
    int     col;
    int     nb;

    col = 0;
    table = ft_split(line, ' ');
    if (!table)
        return (NULL);
    *length = split_array_len(table);
    out = (t_crd *)malloc(sizeof(t_crd) * (*length));
    if (!out)
        return (NULL);
    while (table[col] != NULL)
    {
        nb = ft_atoi(table[col]);
        if (nb == 0 && table[col][0] != '0')
        {
            col = 0;
            while (table[col] != NULL)
                free(table[col++]);
            free(table);
            free(out);
            return (NULL);
        }
        out[col].x = col;
        out[col].y = y;
        out[col].z = nb;
        col++;
    }
    col = 0;
    while (table[col] != NULL) // Free the split array
        free(table[col++]);
    free(table);
    return (out);
}


char	**load_map(char *filename)
{
  int fd;
  char	*next_line;
	int	y;
	t_crd *map;

  fd = open(filename);
	y = 0;
  if (!check_extension(filename, ".fdf") || fd < 1)
  {
    ft_printf("(%s) is not a valid filename or could not be found.", filename);
    return NULL;
  }
  while (1)
  {
    next_line = get_next_line(fd);
    if (next_line == NULL)
        break ;
		// handle line here
    next_line = NULL;
  }
  close(fd);
  return (0);
}

int main(void)
{
    char line[] = "1 2 3 4 5";
    int length;
    t_crd *crds = convert_line_into_crds(line, 0, &length);
    if (!crds)
    {
        printf("Error converting line into crds.\n");
        return (1);
    }
    for (int i = 0; i < length; i++)
    {
        printf("x: %d, y: %d, z: %d\n", crds[i].x, crds[i].y, crds[i].z);
    }
    free(crds);
    return (0);
}
