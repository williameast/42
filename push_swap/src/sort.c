/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <weast@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:55 by William           #+#    #+#             */
/*   Updated: 2024/11/22 20:27:54 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"


void	check_output(t_stack *stack)
{
	t_node	*temp;

	temp = stack->top;
	while (temp->next != NULL)
	{
		if (temp->n > temp->next->n)
		{
			printf("<<<<<<<<<<<<<<<<<<<FAIL>>>>>>>>>>>>>>>>>\n");
			return;
		}
		temp = temp->next;
	}
	printf("<<<<<<<<<<<<<<<<<<<SUCCESS>>>>>>>>>>>>>>>>>\n");
	return;
}

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
	willysort(a, b);
	check_output(a);
    return 0;
}

