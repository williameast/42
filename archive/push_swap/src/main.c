/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:57:10 by weast             #+#    #+#             */
/*   Updated: 2024/11/12 15:18:53 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/push_swap.h"

void	handle_triplets(t_node **stack)
{
    if (is_ascending(stack))
    {
        ft_putstr_fd("stack a is sorted.", 0);
        return ;
    }
    if (list_len(stack) != 2)
    {
        ft_putstr_fd("error: stack longer than 3", 0);
        return ;
    }
}

void	init_stacks(t_node **a, t_node **b, t_moves *seq)
{
    if (is_ascending(a))
        return ;
    get_move_cost(a);
    /* print_movseq(seq); */
    apply_movseq(a, b, seq);
    return ;
}

t_moves	*simulate_moves(t_node **sim_a)
{
    t_node	*sim_b;
    t_moves	*sim_seq;
    int	len;
    int	min_cost;

    if (is_ascending(sim_a))
        return (NULL);
    sim_b = NULL;
    sim_seq = init_movseq(50);
    len = list_len(sim_a);
    while (len > 0)
	{
        get_move_cost(sim_a);
        min_cost = get_min_cost(sim_a);
        while (min_cost > 1)
        {
            apply_single_move(sim_a, &sim_b, 6);
            add_move(sim_seq, 6);
            get_move_cost(sim_a);
            min_cost = get_min_cost(sim_a);
        }
        while (min_cost <= -1)
            {
                apply_single_move(sim_a, &sim_b, 9);
                add_move(sim_seq, 9);
                min_cost = get_min_cost(sim_a);
                min_cost++;
            }
        apply_single_move(sim_a, &sim_b, 4);
        add_move(sim_seq, 4);
        len--;
    }
    len = list_len(&sim_b);
    while (len > 0)
    {
        apply_single_move(sim_a, &sim_b, 3);
        add_move(sim_seq, 3);
        len--;
    }
    return (sim_seq);
}

int	main(int argc, char *argv[])
{
    t_node	*a;
    t_node	*b;
    t_node	*sim_a;
    /* t_moves *seq; */
    /* int	*arr; */
    /* int	result_len = 0; */

    a = NULL;
    b = NULL;
    if (argc == 2)
    {
        a = get_int_from_str(argv[1]);
        sim_a = get_int_from_str(argv[1]);
    }
    else
    {
        a = get_int_from_argv(argc, argv);
        sim_a = get_int_from_argv(argc, argv);
    }
    if (a == NULL || check_for_dup_in_stack(&a))
    {
        ft_putstr_fd("Error\n", 2);
        free_list(a);
        free_list(sim_a);
        return (0);
    }
    /* print_stack(&a); */
    /* prep_stack_b(&a, &b); */
    printf("bits: %i\n", get_max_bits(&a));
    print_both(&a, &b);
    /* apply_movseq(&a, &b, seq); */
    free_list(sim_a);
    free_list(a);
    free_list(b);
    return 0;
}
