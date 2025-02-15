/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:48:49 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 21:25:27 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

static void	reverse_rotate(t_stack *stack);

/**
 * @brief Reverse Rotate the stack
 * @param stack Stack to reverse rotate
 * @details Move the bottom node to the top of the stack
 */
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

/**
 * @brief Reverse Rotate the stack A
 * @param a Stack A
 * @param op_list List of operations needed to sort the stacks
 */
void	rra(t_stack *a, t_operation **op_list)
{
	reverse_rotate(a);
	add_operation(op_list, "rra");
}

/**
 * @brief Reverse Rotate the stack B
 * @param b Stack B
 * @param op_list List of operations needed to sort the stacks
 */
void	rrb(t_stack *b, t_operation **op_list)
{
	reverse_rotate(b);
	add_operation(op_list, "rrb");
}

/**
 * @brief Reverse Rotate the stack A and B
 * @param a Stack A
 * @param b Stack B
 * @param op_list List of operations needed to sort the stacks
 */
void	rrr(t_stack *a, t_stack *b, t_operation **op_list)
{
	reverse_rotate(a);
	reverse_rotate(b);
	add_operation(op_list, "rrr");
}
