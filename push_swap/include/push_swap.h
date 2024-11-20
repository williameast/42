/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:38:00 by weast             #+#    #+#             */
/*   Updated: 2024/11/14 14:16:34 by William          ###   ########.fr       */
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
    int	target;
    struct s_node	*next;
}	t_node;


typedef struct s_stack
{
    t_node	*top;
    char	name;
} t_stack;

typedef struct s_moves
{
    int	*moves;
    int	size;
    int	capacity;
}	t_moves;

/* declarations */
/* Declarations from sanitize.c */
t_stack	*init_stack(char c);
int	check_for_dup_in_stack(t_stack *stack);
t_stack	*get_int_from_str(char *str);
t_stack	*get_int_from_argv(int argc, char **argv);

/* Declarations from utils.c */
int	stack_size(t_stack *stack);
int	get_max_bits(t_stack *stack);
void	index_stack(t_stack *stack);
int	find_closest_smaller_nr(t_stack *stack, int nr);
int find_closest_position(t_stack *stack, int nr);
void	get_targets(t_stack *a, t_stack *b);
void	get_cost(t_stack *stack);
int	ft_abs(int nr);
int	find_cheapest_candidate(t_stack *a);
int	find_cheapest_target(t_stack *a);
void	rotate_n_times(t_stack *stack, int cost);
int	find_max(t_stack *stack);
void	move_max_to_top(t_stack *stack);
void	funnysort(t_stack *a, t_stack *b);

/* Declarations from lists.c */
void	print_move(char *move, char stack);
void push(t_stack *stack, int value);
void	push_to_stack(t_stack *src, t_stack *dest);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);
void print_stack(t_stack *stack);

/* Declarations from sort.c */
int	main(int argc, char *argv[]);

/* Declarations from printing.c */
void	print_stack_v(t_node **head);
void	print_both(t_stack *a, t_stack *b);
void	print_movseq(t_moves *seq);
char	*debug_decode_movseq(int move);
void	print_array(int *arr, int size);

/* declarations end */


#endif // PUSH_SWAP_H_

