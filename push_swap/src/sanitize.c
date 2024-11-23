/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:38:24 by weast             #+#    #+#             */
/*   Updated: 2024/11/23 17:04:22 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/push_swap.h"

t_stack	*init_stack(char c)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (stack == NULL)
		return (NULL);
	stack->top = NULL;
	stack->name = c;
	return (stack);
}

void	index_stack(t_stack *stack)
{
	t_node	*current;
	int		index;

	index = 0;
	current = stack->top;
	while (current != NULL)
	{
		current->index = index;
		index++;
		current = current->next;
	}
}

int	check_for_dup_in_stack(t_stack *stack)
{
	t_node	*needle;
	t_node	*haystack;

	needle = stack->top;
	while (needle != NULL)
	{
		haystack = needle->next;
		while (haystack != NULL)
		{
			if (needle->n == haystack->n)
				return (1);
			haystack = haystack->next;
		}
		needle = needle->next;
	}
	return (0);
}

t_stack	*get_int_from_str(char *str)
{
	t_stack	*stack_a;
	char	**res;
	int		i;
	int		nb;

	i = 0;
	stack_a = init_stack('a');
	res = ft_split(str, ' ');
	while (res[i] != NULL)
	{
		nb = ft_atoi(res[i]);
		if ((nb == 0 && res[i][0] != '0'))
		{
			free(res[i]);
			free(res);
			free_stack(stack_a);
			return (NULL);
		}
		push(stack_a, nb);
		free(res[i]);
		i++;
	}
	free(res);
	return (stack_a);
}

t_stack	*get_int_from_argv(int argc, char **argv)
{
	t_stack	*stack_a;
	int		i;
	int		nb;

	i = 1;
	stack_a = init_stack('a');
	while (i < argc)
	{
		if (ft_strchr(argv[i], ' '))
		{
			free_stack(stack_a);
			return (NULL);
		}
		nb = ft_atoi(argv[i]);
		if ((nb == 0 && argv[i][0] != '0'))
		{
			free_stack(stack_a);
			return (NULL);
		}
		push(stack_a, nb);
		i++;
	}
	return (stack_a);
}
