/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:38:24 by weast             #+#    #+#             */
/*   Updated: 2024/09/27 14:23:51 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/push_swap.h"

int	check_for_dup_in_stack(t_node **head)
{
    t_node	*needle;
    t_node	*haystack;

    needle = *head;
    while (needle != NULL)
    {
        haystack = needle->next;
        while (haystack !=NULL)
        {
            if (needle->n == haystack->n)
                return (1);
            haystack = haystack->next;
        }
        needle = needle->next;
        }
    return (0);
}


t_node	*get_int_from_str(char *str)
{
    char	**res;
    t_node	*stack_a;
    int	i;
    int	nb;

    i = 0;
    stack_a = NULL;
    res = ft_split(str, ' ');
    while (res[i] != NULL)
    {
        nb = ft_atoi(res[i]);
        if ((nb == 0 && res[i][0] != '0'))
        {
            free(res[i]);
            free(res);
            return NULL;
        }
        append_node(&stack_a, nb);
        free(res[i]);
        i++;
    }
    free(res);
    return (stack_a);
}

t_node	*get_int_from_argv(int argc, char **argv)
{
    t_node *stack_a;
    int	i;
    int	nb;

    i = 1;
    stack_a = NULL;
    while (i < argc)
    {
        if (ft_strchr(argv[i], ' '))
            return (NULL);
        nb = ft_atoi(argv[i]);
        if ((nb == 0 && argv[i][0] != '0'))
            return NULL;
        append_node(&stack_a, nb);
        i++;
    }
    return (stack_a);
}
