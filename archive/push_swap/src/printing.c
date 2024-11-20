/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:32:12 by weast             #+#    #+#             */
/*   Updated: 2024/10/07 17:24:01 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*           print the full stack, in the order it is currently in.           */
/*                                                                            */
/* ************************************************************************** */
#include "../include/push_swap.h"

void	print_stack(t_node **head)
{
    t_node	*temp;

    temp = *head;
    while (temp != NULL)
    {
        ft_putnbr_fd(temp->n, 0);
        ft_putchar_fd(' ', 0);
        temp = temp->next;
    }
    ft_putchar_fd('\n', 0);
}

void	print_stack_v(t_node **head)
{
    t_node	*temp;

    temp = *head;
    while (temp != NULL)
    {
        printf("ID:%i VAL: %i\n", temp->index, temp->n);
        temp = temp->next;
    }
    ft_putchar_fd('\n', 0);
}

void	print_both(t_node **a, t_node **b)
{
    t_node *temp_a = *a;
    t_node *temp_b = *b;

    printf("%-25s %-15s\n", "STACK A", "STACK B");
    printf("%-5s %-11s %-5s | %-5s %-11s %-5s\n", "id", "value", "cost", "id", "value", "cost");

    while (temp_a != NULL || temp_b != NULL)
    {
        if (temp_a != NULL && temp_b != NULL)
        {
            printf("%-5d %-11d %-5d |  %-5d %-11d %-5d\n", temp_a->index, temp_a->n, temp_a->cost, temp_b->index, temp_b->n, temp_b->cost);
            temp_a = temp_a->next;
            temp_b = temp_b->next;
        }
        else if (temp_a != NULL)
        {
            printf("%-5d %-11d %-5d |  %-5s %-11s %-5s\n", temp_a->index, temp_a->n, temp_a->cost, "", "", "");
            temp_a = temp_a->next;
        }
        else if (temp_b != NULL)
        {
            printf("%-5s %-11s %-5s |  %-5d %-11d %-5d\n", "", "", "", temp_b->index, temp_b->n, temp_b->cost);
            temp_b = temp_b->next;
        }
    }
}

/* ************************************************************************** */
/*                                                                            */
/*sa 0 |sb 1 |ss 2 |pa 3 |pb 4 |pp 5 |ra 6 |rb 7 |rr 8 |rra 9 |rrb 10 |rrr 11 */
/*                                                                            */
/* ************************************************************************** */

void	print_movseq(t_moves *seq)
{
    int	i;
    i = 0;
    char *movenames[] = {"sa", "sb", "ss", "pa", "pb", "pp", "ra", "rb", "rr", "rra", "rrb", "rrr"};

    if (!seq)
        return;
    /* printf("%s\n", "MOVSEQ"); */
    while (i < seq->size)
    {
        ft_putstr_fd(movenames[seq->moves[i]], 0);
        ft_putstr_fd("\n", 0);
        i++;
    }
    /* printf("MOVSEQ completed in %i moves.\n", i); */
}

char	*debug_decode_movseq(int move)
{
    char *movenames[] = {"sa", "sb", "ss", "pa", "pb", "pp", "ra", "rb", "rr", "rra", "rrb", "rrr"};
    return (movenames[move]);
}

void	print_array(int *arr, int size)
{
    int 	i;
    i = 0;
    while (i < size)
    {
        printf("%i ", arr[i]);
        i++;
    }
    printf("\n");
}
