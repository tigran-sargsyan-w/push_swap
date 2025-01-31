/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:03:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/31 21:21:26 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/ft_printf.h"

// find minimum index in the stack
int find_min_index(t_stack *stack)
{
    t_node *current;
    int min;

    if (!stack || !stack->top)
        return (0);
        
    current = stack->top;
    min = current->index;
    while (current)
    {
        if (current->index < min)
            min = current->index;
        current = current->next;
    }
    return min;
}

// find maximum index in the stack
int find_max_index(t_stack *stack)
{
    t_node *current;
    int max;

    if (!stack || !stack->top)
        return (0);

    current = stack->top;
    max = current->index;
    while (current)
    {
        if (current->index > max)
            max = current->index;
        current = current->next;
    }
    return (max);
}

// sort the stack using radix sort
void    radix_sort(t_stack *a, t_stack *b, int size)
{
    int i;
    int bit;
    int max_bits;
    int max_index;

    bit = 0;
    max_bits = 0;
    max_index = find_max_index(a);
    while ((max_index >> max_bits) != 0)
        max_bits++;
    while (bit < max_bits)
    {
        i = 0;
        while (i < size)
        {
            if (((a->top->index >> bit) & 1) == 1)
                ra(a);
            else
                pb(a, b);
            i++;
        }
        while (!stack_is_empty(b))
            pa(a, b);
        bit++;
    }
}
