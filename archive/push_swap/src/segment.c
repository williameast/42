/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:07:52 by weast             #+#    #+#             */
/*   Updated: 2024/10/07 17:40:02 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	arr_swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

static int choose_pivot(int *arr, int lo, int hi)
{
    int mid = lo + (hi - lo) / 2;

    if (arr[lo] > arr[mid])
        arr_swap(&arr[lo], &arr[mid]);
    if (arr[lo] > arr[hi])
        arr_swap(&arr[lo], &arr[hi]);
    if (arr[mid] > arr[hi])
        arr_swap(&arr[mid], &arr[hi]);

    arr_swap(&arr[lo], &arr[mid]);

    return arr[lo];
}

static int	partition(int *arr, int lo, int hi)
{
    int	p;
    int	i;
    int	j;

    p = choose_pivot(arr, lo, hi);
    i = lo;
    j = hi;
    while (i < j)
    {
        while (arr[i] <= p && i <= hi - 1)
            i++;
        while (arr[j] > p && j >= lo + 1)
            j--;
        if (i < j)
            arr_swap(&arr[i], &arr[j]);
    }
    arr_swap(&arr[lo], &arr[j]);
    return (j);
}

static void	ft_qsort(int *arr, int lo, int hi)
{
    int	partition_index;
    if (lo < hi)
        {
            partition_index = partition(arr, lo, hi);
            ft_qsort(arr, lo, partition_index - 1);
            ft_qsort(arr, partition_index + 1, hi);
        }
}

int *get_sorted_array_from_list(t_node **a)
{
    t_node *temp;
    int	*res;
    int	i;
    int	size;

    temp = *a;
    i = 0;
    size = list_len(a);
    res = malloc((sizeof(int) * size));
    if (!res)
        return (NULL);
    while (temp != NULL)
    {
        res[i++] = temp->n;
        temp = temp->next;
    }
    i = 0;
    ft_qsort(res, 0, size - 1);
    return (res);
}

//note that min and max are edge cases!!!!!
int	*get_segment_max_values(int *arr, int segments, int len, int *result_len)
{

    int	*res;
    int	j;

    *result_len = len / segments;
    res = malloc(sizeof(int) * (*result_len));
    if (!res)
        return (NULL);
    j = 0;
    for (int i = segments - 1; i < len; i += segments)
        res[j++] = arr[i];
    print_array(res, *result_len);
    return (res);
}

/* // youll need to likely free the input here. not used. */
/* int *get_segment_cutoff_values(int	*arr, int segments, int len) */
/* { */
/*     int	*res; */
/*     int segment_size; */
/*     int remainder; */
/*     int sum; */
/*     int count; */
/*     int i; */
/*     int j; */
/*     int k; */

/*     i = 0; */
/*     j = 0; */
/*     k = 0; */
/*     sum = 0; */
/*     segment_size = len / segments; */
/*     remainder = len % segments; */
/*     res = malloc(sizeof(int) * segments); */
/*     if (!res) */
/*         return (NULL); */
/*     zero_array(res, segments); */
/*     while (j < segments) */
/*         { */
/*             sum = 0; */
/*             if (remainder > 0) */
/*                 { */
/*                     count = segment_size + 1; */
/*                     remainder--; */
/*                 } */
/*             else */
/*                 count = segment_size; */
/*             while (k < count) */
/*             { */
/*                 sum += arr[i]; */
/*                 i++; */
/*                 k++; */
/*             } */
/*             k = 0; */
/*             res[j] = sum / count; */
/*             j++; */
/*         } */

/*     print_array(res, segments); */
/*     return (res); */
/* } */
