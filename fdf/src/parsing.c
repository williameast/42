/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:50:32 by William           #+#    #+#             */
/*   Updated: 2025/01/20 12:42:07 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	process_row(t_map *map, char *row, int row_index)
{
	int		row_count;
	t_crd	*row_coords;

	row_count = 0;
	row_coords = parse_row_to_coordinates(row, row_index, &row_count);
	if (!row_coords)
		return (0);
	if (!append_row_to_map(map, row_coords, row_count))
	{
		free(row_coords);
		return (0);
	}
	free(row_coords);
	return (1);
}

// Function to read the full map as a single string
static char	*read_full_map_as_str(char *file)
{
	int		fd;
	char	*full_line;
	char	*next_line;
	char	*temp;

	full_line = ft_strdup("");
	fd = open(file, O_RDONLY);
	if (fd < 0 || !check_extension(file, ".fdf"))
	{
		ft_printf("ERROR: <%s> is not valid or could not be found.\n", file);
		free(full_line);
		return (NULL);
	}
	next_line = get_next_line(fd);
	while (next_line != NULL)
	{
		temp = ft_strjoin(full_line, next_line);
		free(full_line);
		full_line = temp;
		free(next_line);
		next_line = get_next_line(fd);
	}
	close(fd);
	return (full_line);
}

// Function to read and split the map file into rows
char	**read_and_split_map(char *filename)
{
	char	*map_str;
	char	**row_split;

	map_str = read_full_map_as_str(filename);
	if (DEBUG)
		ft_printf("INFO: map string: \n%s\n", map_str);
	if (!map_str)
		return (NULL);
	row_split = ft_split(map_str, '\n');
	free(map_str);
	if (!row_split)
		ft_printf("ERROR: Failed to split map string into rows.\n");
	return (row_split);
}

int	populate_map(t_map *map, char **row_split)
{
	int	i;

	i = 0;
	while (row_split[i] != NULL)
	{
		if (!process_row(map, row_split[i], i))
			return (0);
		i++;
	}
	get_coordinate_limits(map);
	return (1);
}

t_map	*parse_map(char *filename)
{
	char	**row_split;
	t_map	*map;

	row_split = read_and_split_map(filename);
	if (!row_split)
		return (NULL);
	map = init_map();
	if (!map)
	{
		free_char_array(row_split);
		return (NULL);
	}
	if (!populate_map(map, row_split))
	{
		free_map(map);
		free_char_array(row_split);
		return (NULL);
	}
	free_char_array(row_split);
	return (map);
}

/* t_map	*parse_map(char *filename) */
/* { */
/*     char **row_split; */
/* 	t_map	*map; */
/*     int	i; */

/*     i = 0; */
/* 	row_split = read_and_split_map(filename); */
/*     if (!row_split) */
/* 		return NULL; */
/* 	map = init_map(); */
/*     if (!map) */
/*     { */
/*         free_char_array(row_split); */
/*         return NULL; */
/*     } */
/*     while (row_split[i] != NULL) */
/*     { */
/*         if (!process_row(map, row_split[i], i)) */
/*         { */
/*             free_map(map); */
/*             free_char_array(row_split); */
/*             return NULL; */
/*         } */
/*         i++; */
/*     } */
/*     free_char_array(row_split); */
/*     get_coordinate_limits(map); */
/*     return map; */
/* } */
