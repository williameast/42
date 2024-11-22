/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:55 by William           #+#    #+#             */
/*   Updated: 2024/11/22 22:17:37 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int find_closest_larger_index(t_stack *stack, int nr, int *closest_larger_value)
{
    t_node *temp;
    int closest_larger_index;
    int current_index;

    temp = stack->top;
    closest_larger_index = -1;
    current_index = 0;
    while (temp != NULL)
    {
        if (temp->n > nr && temp->n < *closest_larger_value)
        {
            *closest_larger_value = temp->n;
            closest_larger_index = current_index;
        }
        current_index++;
        temp = temp->next;
    }
    return closest_larger_index;
}

int find_smallest_index(t_stack *stack, int *smallest_value)
{
    t_node *temp;
    int smallest_index;
    int current_index;

    temp = stack->top;
    smallest_index = -1;
    current_index = 0;
    while (temp != NULL)
    {
        if (temp->n < *smallest_value)
        {
            *smallest_value = temp->n;
            smallest_index = current_index;
        }
        current_index++;
        temp = temp->next;
    }
    return smallest_index;
}

int calculate_shortest_distance(int target_index, int stack_size)
{
    int rotate_distance;
    int reverse_rotate_distance;

    rotate_distance = target_index;
    reverse_rotate_distance = target_index - stack_size;
    if (ft_abs(rotate_distance) <= ft_abs(reverse_rotate_distance))
        return rotate_distance;
    return reverse_rotate_distance;
}

int find_closest_position_ascending(t_stack *stack, int nr)
{
    int closest_larger_value;
    int smallest_value;
    int size;
    int closest_larger_index;
    int smallest_index;
    int target_index;

    closest_larger_value = INT_MAX;
    smallest_value = INT_MAX;
    size = stack_size(stack);
    closest_larger_index = find_closest_larger_index(stack, nr, &closest_larger_value);
    smallest_index = find_smallest_index(stack, &smallest_value);
    if (closest_larger_index != -1)
        target_index = closest_larger_index;
    else
        target_index = smallest_index;
    return calculate_shortest_distance(target_index, size);
}
