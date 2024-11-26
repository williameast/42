
#include "/include/push_swap.h"

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
void	print_both(t_stack *a, t_stack *b)
{
    t_node *temp_a = a->top;
    t_node *temp_b = b->top;

    printf("%-25s %-15s\n", "STACK A", "STACK B");
    printf("%-5s %-11s %-5s | %-5s %-11s %-5s\n", "target", "value", "cost", "target", "value", "cost");

    while (temp_a != NULL || temp_b != NULL)
    {
        if (temp_a != NULL && temp_b != NULL)
        {
            printf("%-5d %-11d %-5d |  %-5d %-11d %-5d\n", temp_a->target, temp_a->n, temp_a->cost, temp_b->target, temp_b->n, temp_b->cost);
            temp_a = temp_a->next;
            temp_b = temp_b->next;
        }
        else if (temp_a != NULL)
        {
            printf("%-5d %-11d %-5d |  %-5s %-11s %-5s\n", temp_a->target, temp_a->n, temp_a->cost, "", "", "");
            temp_a = temp_a->next;
        }
        else if (temp_b != NULL)
        {
            printf("%-5s %-11s %-5s |  %-5d %-11d %-5d\n", "", "", "", temp_b->target, temp_b->n, temp_b->cost);
            temp_b = temp_b->next;
        }
    }
}
