/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:38:00 by weast             #+#    #+#             */
/*   Updated: 2024/11/12 18:39:11 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H_
#define PUSH_SWAP_H_

# include "../libft/libft.h"


# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_node
{
    int	n;
    int	index;
    int	cost;
    int	distance;
    struct s_node	*next;
}	t_node;

typedef struct s_moves
{
    int	*moves;
    int	size;
    int	capacity;
}	t_moves;

/* declarations */
/* Declarations from sanitize.c */
int	check_for_dup_in_stack(t_node **head);
t_node	*get_int_from_str(char *str);
t_node	*get_int_from_argv(int argc, char **argv);

/* Declarations from double_moves.c */
void	swap_both(t_node **a, t_node **b);
void	rotate_both(t_node **a, t_node **b);
void	reverse_rotate_both(t_node **a, t_node **b);
void	push_both(t_node **a, t_node **b);

/* Declarations from segment.c */
int *get_sorted_array_from_list(t_node **a);
int	*get_segment_max_values(int *arr, int segments, int len, int *result_len);

/* Declarations from utils.c */
int	is_ascending(t_node **head);
int	is_decending(t_node **head);
int	get_max(t_node **head);
int	get_min(t_node **head);
int	ft_abs(int n);

/* Declarations from main.c */
void	handle_triplets(t_node **stack);
void	init_stacks(t_node **a, t_node **b, t_moves *seq);
t_moves	*simulate_moves(t_node **sim_a);
int	main(int argc, char *argv[]);

/* Declarations from turk.c */
int	get_last(t_node **stack);
int get_max_bits(t_node **stack);
void	bit_sort(t_node **stackA, t_node **stackB);
void	prep_stack_b(t_node **stackA, t_node **stackB);
int	cost_to_move_bw_neighbours(t_node **stack, int nr);

/* Declarations from list_mgmt.c */
t_node	*generate_node(int n);
void	append_node(t_node **head, int n);
int	list_len(t_node **head);
void	index_list(t_node **head);
void	free_list(t_node *head);

/* Declarations from printing.c */
void	print_stack(t_node **head);
void	print_stack_v(t_node **head);
void	print_both(t_node **a, t_node **b);
void	print_movseq(t_moves *seq);
char	*debug_decode_movseq(int move);
void	print_array(int *arr, int size);

/* Declarations from moveseq.c */
t_moves *init_movseq(int initial_capacity);
int	add_move(t_moves *seq, int move);
void	free_movseq(t_moves *seq);
void	apply_movseq(t_node **a, t_node **b, t_moves *seq);
void	apply_single_move(t_node **a, t_node **b, int move);

/* Declarations from cost_calculator.c */
void	get_move_cost(t_node **head);
int	get_max_cost(t_node **head);
int	get_min_cost(t_node **head);

/* Declarations from algo.c */
void	sort_triplets(int min_cost, int max_cost, t_moves *seq);
void	get_moves_to_extract_max(t_node **a, t_moves *seq);
void	max_sort(t_node **a, t_moves *seq);
t_moves	*bin_sort(t_node **a, int segments);

/* Declarations from ops.c */

/* Declarations from movements.c */
void	swap(t_node **stack);
void	rotate(t_node **stack);
void	reverse_rotate(t_node **stack);
void	push(t_node **src_stack, t_node **dest_stack);

/* declarations end */


#endif // PUSH_SWAP_H_

