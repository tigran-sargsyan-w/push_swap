/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:03:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/27 23:32:19 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// find the maximum index in the stack
int find_min_index(t_stack *a)
{
    t_node *current = a->top;
    int min = current->index;
    while (current)
    {
        if (current->index < min)
            min = current->index;
        current = current->next;
    }
    return min;
}

int find_max_index(t_stack *a)
{
    t_node *current;
    int max;

    if (!a || !a->top)
        return (0); // или обработка ошибки

    current = a->top;
    max = current->index;
    while (current)
    {
        if (current->index > max)
            max = current->index;
        current = current->next;
    }
    return (max);
}

// Bitwise Radix Sort
// void radix_sort(t_stack *a, t_stack *b, int size)
// {
    // int min_in_stack = find_min_index(a);
    // int min_index = 0;
    // t_node	*current;
    // int i = 0;
    // int j = 0;
// 
    // current = a->top;
    // while (current)
    // {
        // min_in_stack = find_min_index(a);
        // while (a ->top->index != min_in_stack)
        // {
            // ra(a);
        // }
        // current = current->next;
        // pb(a, b);
        // print_stack(a);
        // print_stack_index(a);
        // 
    // }
    // 
    // while (b->size > 0)
    // {
        // pa(a, b);
    // }
    // 
    // 
// }

void    radix_sort(t_stack *a, t_stack *b, int size)
{
    int max_index;
    int max_bits;
    int bit;
    int i;

    max_index = find_max_index(a); // находит крупнейший index
    max_bits = 0;
    while ((max_index >> max_bits) != 0)
        max_bits++;

    bit = 0;
    while (bit < max_bits)
    {
        i = 0;
        while (i < size)
        {
            // Смотрим текущий бит вершины
            if (((a->top->index >> bit) & 1) == 1)
                ra(a);
            else
                pb(a, b);
            i++;
        }
        // Возвращаем все из B обратно
        while (!stack_is_empty(b))
            pa(a, b);

        bit++;
    }
}
