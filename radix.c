/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:03:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/28 19:13:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/ft_printf.h"

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
            if (((a->top->index >> bit) & 1) == 1)
            {
                ra(a);
                // print_stack(a);
            }
            else
            {
                pb(a, b);
            }
            i++;
        }

        while (!stack_is_empty(b))
            pa(a, b);

        bit++;
    }
}
