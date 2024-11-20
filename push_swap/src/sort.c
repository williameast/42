/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:55 by William           #+#    #+#             */
/*   Updated: 2024/11/20 19:02:10 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char *argv[])
{
    t_stack	*a;
    t_stack	*b;


    if (argc == 2)
        a = get_int_from_str(argv[1]);
    else
        a = get_int_from_argv(argc, argv);

    if (a == NULL || check_for_dup_in_stack(a))
    {
        ft_putstr_fd("Error\n", 2);
        return (0);
    }
	b = init_stack('b');
	printf("INPUT:\n");
	print_both(a, b);
	printf("INPUT END\n\n\n");
	willysort(a, b);
	printf("OUTPUT:\n");
	print_both(a, b);
    return 0;
}

