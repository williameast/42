/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:07:33 by William           #+#    #+#             */
/*   Updated: 2024/12/13 16:31:55 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


/* void	test_atoi(char *str) */
/* { */
/* 	int mine = ft_atoi(str); */
/* 	int original = atoi(str); */


/* 	printf("TEST [i]: %s\n", str); */
/* 	printf("atoi: <%i>, ft_atoi <%i>\n", original, mine); */
/* 	if (original == mine) */
/* 		printf("PASS\n"); */
/* 	else */
/* 		printf("FAIL\n"); */
/* } */

/* int	main(void) */
/* { */

/* 	test_atoi("42"); */
/* 	test_atoi("-42"); */
/* 	test_atoi(" 123"); */
/* 	test_atoi("123 "); */
/* 	test_atoi(" 123 "); */
/* 	test_atoi(" abc "); */
/* 	test_atoi(" 42abc "); */
/* 	test_atoi("999999999999999"); */
/* } */

int main(int argc, char **argv)
{
	char	*map_str;
	t_crd	*map;
	int	*map_len;

	map_len = 0;
    if (argc != 2)
    {
        ft_printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
	map_str = read_full_map_as_str(argv[1]);
	map = parse_map(map_str, map_len);
	print_coordinates(map, map_len);
    if (!map)
    {
        ft_printf("ERROR: Error loading map.\n");
        return 1;
    }
	ft_printf("%s", map);
	free(map);
}
