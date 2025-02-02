/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:48:49 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/02 19:11:06 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"

// Reverse Rotate
static void	reverse_rotate(t_stack *stack)
{
	t_node	*last;

	if (!stack || stack->size < 2)
		return ;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
}

// Reverse Rotate A
void	rra(t_stack *a, t_operation **op_list)
{
	reverse_rotate(a);
	add_operation(op_list, "rra");
}

// Reverse Rotate B
void	rrb(t_stack *b, t_operation **op_list)
{
	reverse_rotate(b);
	add_operation(op_list, "rrb");
}

// Reverse Rotate A и B
void	rrr(t_stack *a, t_stack *b, t_operation **op_list)
{
	reverse_rotate(a);
	reverse_rotate(b);
	add_operation(op_list, "rrr");
}
