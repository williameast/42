/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:48:38 by William           #+#    #+#             */
/*   Updated: 2024/12/08 19:46:36 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	split_array_len(char **arr)
{
	int	i;
	i = 0;

	while (arr[i] != NULL)
		i++;
	return (i);
}
// custom realloc
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

// check if the filename has the appropriate extension.
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

// initialize a map.
t_map *init_map(void)
{
	t_map	*map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->rows = 0;
	map->cols = 0;
	ft_printf("INFO: map initisalized.\n");
	return (map);
}

// walk through a map, freeing each column as it walks through the rows. then frees the obj itself.
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < map->rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}

void free_split(char **split)
{
    int i = 0;

	if (!split)
		return ;
    while (split[i])
        free(split[i]);
    free(split);
}


int *parse_line(char *line, int cols)
{
    char **split_line;
    int *row;
    int i;
    int nb;

    i = 0;
    ft_printf("INFO: Entering parse_line\n");
    split_line = ft_split(line, ' ');
    if (!split_line)
    {
        ft_printf("ERROR: split_line allocation failed\n");
        return (NULL);
    }
    ft_printf("INFO: split line successful\n");

    row = malloc(sizeof(int) * cols);
    if (!row)
    {
        ft_printf("ERROR: row allocation failed\n");
        free_split(split_line); // Free split_line before returning
        return (NULL);
    }
    ft_printf("INFO: Allocated row, cols: %i\n", cols);

    while (i < cols && split_line[i])
    {
        ft_printf("INFO: Processing split_line[%i]: %s\n", i, split_line[i]);
        nb = ft_atoi(split_line[i]);
        if (nb == 0 && split_line[i][0] != '0')
        {
            ft_printf("ERROR: Invalid number in line at index %i: %s\n", i, split_line[i]);
            free_split(split_line);
            free(row);
            return (NULL);
        }
        row[i] = nb;
        ft_printf("INFO: Parsed number: %i into row[%i]\n", nb, i);
        free(split_line[i]); // Free individual split element
        i++;
    }

    ft_printf("INFO: Finished parsing line\n");
    free(split_line); // Free the array of pointers itself
    return (row);
}


// Function to resize the map's array and add a new row
int add_row_to_map(t_map *map, int *row)
{
    int **new_grid;

	printf("INFO: adding row to map\n");
    new_grid = ft_realloc(map->grid, sizeof(int *) * map->rows, sizeof(int *) * (map->rows + 1));
    if (!new_grid)
        return (0);
    map->grid = new_grid;
    map->grid[map->rows] = row;
    map->rows++;
    return (1);
}

t_map	*load_map(char *filename)
{
	int	fd;
	char *next_line;
	t_map *map;
	int	*row;

	map = init_map();
	if (map == NULL || (fd = open(filename, O_RDONLY)) < 0 || !check_extension(filename, ".fdf"))
	{
		ft_printf("ERROR: <%s> is not valid or could not be found.\n", filename);
		free_map(map);
		return (NULL);
	}
	while ((next_line = get_next_line(fd)) != NULL)
	{
		if (map->cols == 0)
			map->cols = split_array_len(ft_split(next_line, ' '));
		ft_printf("INFO: preparing to parse line...\n");
		ft_printf("line: %s, map cols: %i \n", next_line, map->cols);
		row = parse_line(next_line, map->cols);
		free(next_line);
		if (!row || !add_row_to_map(map, row))
		{
			ft_printf("ERROR: line processing failed.\n");
			free_map(map);
			close(fd);
			return (NULL);
		}
	}
	close(fd);
	printf("INFO: closed file with fd: %i", fd);
	return (map);
}


void	print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->cols)
	{
		while(j < map->rows)
		{
			ft_printf("%i ", map->grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	free_map(map);
}

int main(int argc, char **argv)
{
    t_map *map;

    if (argc != 2)
    {
        ft_printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    map = load_map(argv[1]);
    if (!map)
    {
        ft_printf("ERROR: Error loading map.\n");
        return 1;
    }

    ft_printf("Map (%d rows x %d cols):\n", map->rows, map->cols);
    for (int x = 0; x < map->rows; x++)
    {
        for (int y = 0; y < map->cols; y++)
            ft_printf("%d ", map->grid[x][y]);
        ft_printf("\n");
    }

    free_map(map);
    return 0;
}
