/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:38:00 by weast             #+#    #+#             */
/*   Updated: 2024/11/23 15:09:40 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../lib/libft/libft.h"

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_node
{
	int				n;
	int				index;
	int				cost;
	int				target;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	char	name;
}	t_stack;

/* declarations */
/* Declarations from costs.c */
void	get_cost(t_stack *stack);
int		find_cheapest_candidate(t_stack *a);
int		find_cheapest_target(t_stack *a);

/* Declarations from maths.c */
int		find_min(t_stack *stack);
int		ft_abs(int nr);
int		stack_size(t_stack *stack);

/* Declarations from moves.c */
void	push_to_stack(t_stack *src, t_stack *dest, int print);
void	rotate(t_stack *stack, int print);
void	reverse_rotate(t_stack *stack, int print);
void	swap(t_stack *stack, int print);

/* Declarations from moves_extended.c */
void	push(t_stack *stack, int value);
void	rotate_both(t_stack *a, t_stack *b);
void	reverse_rotate_both(t_stack *a, t_stack *b);

/* Declarations from position_calculator.c */
int		find_closest_smaller(t_stack *stack, int nr, int *closest_sm_v);
int		find_closest_larger(t_stack *stack, int nr, int *closest_lg_v);
int		find_closest_position(t_stack *stack, int nr);
void	get_targets(t_stack *a, t_stack *b);
void	get_targets_ascending(t_stack *a, t_stack *b);

/* Declarations from printing.c */
void	print_move(char *move, char stack);

/* Declarations from reinsert.c */
int		find_closest_larger_index(t_stack *stack, int nr, int *closest_lg_v);
int		find_smallest_index(t_stack *stack, int *smallest_value);
int		calculate_shortest_distance(int target_index, int stack_size);
int		find_closest_position_ascending(t_stack *stack, int nr);

/* Declarations from sanitize.c */
t_stack	*init_stack(char c);
void	index_stack(t_stack *stack);
int		check_for_dup_in_stack(t_stack *stack);
t_stack	*get_int_from_str(char *str);
t_stack	*get_int_from_argv(int argc, char **argv);

/* Declarations from sort.c */
void	sort_triplets(t_stack *stack);
void	slot_b_into_a(t_stack *a, t_stack *b);
void	xdsort(t_stack *src, t_stack *dest, int cutoff);
void	sort_less_than_three(t_stack *stack);
void	willysort(t_stack *a, t_stack *b);
int		main(int argc, char *argv[]);

/* Declarations from utilities.c */
void	rotate_n_times(t_stack *stack, int cost);
void	rotate_n_times_combined(t_stack *a, t_stack *b, int cost_a, int cost_b);
void	move_min_to_top(t_stack *stack);
void	index_and_get_costs_of_stacks(t_stack *a, t_stack *b);
void	free_stack(t_stack *stack);

/* declarations end */

#endif // PUSH_SWAP_H
