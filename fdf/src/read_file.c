/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:59:15 by weast             #+#    #+#             */
/*   Updated: 2024/12/03 00:05:09 by William          ###   ########.fr       */
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

char	**file2tab(char *str, t_param *p)
{
	int		fd;
	char	**tab;
	char	*line;
	char	*file;

	if ((fd = open(str, O_RDONLY)) == -1)
		return (NULL);
	file = ft_strnew(1);
	while (get_next_line(fd, &line))
	{
		file = ft_strf2join(file, line);
		file = ft_strf2join(file, ft_strdup("\n"));
	}
	if (map_dimension(file, p) == -1)
		return (NULL);
	tab = ft_split(file);
	free(file);
	close(fd);
	return (tab);
}


char	**read_as_map(char *line)
{
  char	**table;



}




char	**load_map(char *filename)
{
  int fd;
  char	*next_line;

  fd = open(filename);
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
    ft_printf("%s\n", next_line);
    next_line = NULL;
  }
  close(fd);
  return (0);
}
