/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:20:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/02 18:56:07 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"

// rotate the stack by moving the top node to the bottom
void	rotate(t_stack *stack)
{
	t_node	*first;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	stack->top->prev = NULL;
	first->next = NULL;
	first->prev = stack->bottom;
	stack->bottom->next = first;
	stack->bottom = first;
}

// Rotate A
void	ra(t_stack *a, t_operation **op_list)
{
	rotate(a);
	add_operation(op_list, "ra");
}

// Rotate B
void	rb(t_stack *b, t_operation **op_list)
{
	rotate(b);
	add_operation(op_list, "rb");
}

// Rotate A и B
void	rr(t_stack *a, t_stack *b, t_operation **op_list)
{
	rotate(a);
	rotate(b);
	add_operation(op_list, "rr");
}
