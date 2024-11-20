/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:55 by William           #+#    #+#             */
/*   Updated: 2024/11/14 14:42:40 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

/* void	silly_sort(t_stack *a, t_stack *b) */
/* { */
/* 	int max_bits; */
/* 	int	top_value; */
/* 	int	bit; */
/* 	int	i; */
/* 	int	size; */

/* 	max_bits = get_max_bits(a); */
/* 	i = 0; */
/* 	bit = 0; */
/* 	while (bit++ < max_bits) */
/* 	{ */
/* 		size = stack_size(a); */
/* 		i = 0; */
/* 		while (i++ < size) */
/* 		{ */
/* 			top_value = a->top->n; */
/* 			if ((top_value >> bit) & 1) */
/* 				rotate(a, "ra\n"); */
/* 			else */
/* 				push_to_stack(a, b, "pb\n"); */
/* 		} */
/* 	while(b->top != NULL) */
/* 		push_to_stack(b, a, "pa\n"); */
/* 	} */
/* } */



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
	push_to_stack(a, b);
	push_to_stack(a, b);
	funnysort(a, b);
	/* print_both(a, b); */
    return 0;
}

