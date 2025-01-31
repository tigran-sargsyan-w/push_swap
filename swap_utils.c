/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:10:03 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/31 21:06:20 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"

// swap the top two nodes of the stack
void swap(t_stack *stack)
{
    int temp_val;
    int temp_idx;

    if (!stack || stack->size < 2)
        return;

    // swap value
    temp_val = stack->top->value;
    stack->top->value = stack->top->next->value;
    stack->top->next->value = temp_val;

    // swap index
    temp_idx = stack->top->index;
    stack->top->index = stack->top->next->index;
    stack->top->next->index = temp_idx;
}

// Swap A
void	sa(t_stack *a)
{
	swap(a);
	ft_printf("sa\n");
}

// Swap B
void	sb(t_stack *b)
{
	swap(b);
	ft_printf("sb\n");
}

// Swap A и B
void	ss(t_stack *a, t_stack *b)
{
	swap(a);
	swap(b);
	ft_printf("ss\n");
}
