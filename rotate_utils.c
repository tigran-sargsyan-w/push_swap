/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:20:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/05 11:15:05 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

static void	rotate(t_stack *stack);

/**
 * @brief Rotate the stack
 * @param stack Stack to rotate
 * @details Move the top node to the bottom of the stack
 */
static void	rotate(t_stack *stack)
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

/**
 * @brief Rotate the stack A
 * @param a Stack A
 * @param op_list List of operations needed to sort the stacks
 */
void	ra(t_stack *a, t_operation **op_list)
{
	rotate(a);
	add_operation(op_list, "ra");
}

/**
 * @brief Rotate the stack B
 * @param b Stack B
 * @param op_list List of operations needed to sort the stacks
 */
void	rb(t_stack *b, t_operation **op_list)
{
	rotate(b);
	add_operation(op_list, "rb");
}

/**
 * @brief Rotate the stack A and B
 * @param a Stack A
 * @param b Stack B
 * @param op_list List of operations needed to sort the stacks
 */
void	rr(t_stack *a, t_stack *b, t_operation **op_list)
{
	rotate(a);
	rotate(b);
	add_operation(op_list, "rr");
}
