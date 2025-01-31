/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:20:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/31 21:05:10 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"

// rotate the stack by moving the top node to the bottom
void rotate(t_stack *stack)
{
    t_node *first;

    if (!stack || stack->size < 2)
        return;
    first = stack->top;
    stack->top = first->next;
    stack->top->prev = NULL;
    first->next = NULL;
    first->prev = stack->bottom;
    stack->bottom->next = first;
    stack->bottom = first;
}

// Rotate A
void	ra(t_stack *a)
{
	rotate(a);
	ft_printf("ra\n");
}

// Rotate B
void	rb(t_stack *b)
{
	rotate(b);
	ft_printf("rb\n");
}

// Rotate A и B
void	rr(t_stack *a, t_stack *b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}
