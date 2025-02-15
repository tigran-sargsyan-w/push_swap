/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:10:03 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 17:34:33 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"

static void	swap(t_stack *stack);

/**
 * @brief Swap the top two nodes of the stack
 * @param stack Stack to swap
 */
static void	swap(t_stack *stack)
{
	int	temp_value;
	int	temp_index;

	if (!stack || stack->size < 2)
		return ;
	temp_value = stack->top->value;
	stack->top->value = stack->top->next->value;
	stack->top->next->value = temp_value;
	temp_index = stack->top->index;
	stack->top->index = stack->top->next->index;
	stack->top->next->index = temp_index;
}

/**
 * @brief Swap the top two nodes of the stack A
 * @param a Stack A
 * @param op_list List of operations needed to sort the stacks
 */
void	sa(t_stack *a, t_operation **op_list)
{
	swap(a);
	add_operation(op_list, "sa");
}

/**
 * @brief Swap the top two nodes of the stack B
 * @param b Stack B
 * @param op_list List of operations needed to sort the stacks
 */
void	sb(t_stack *b, t_operation **op_list)
{
	swap(b);
	add_operation(op_list, "sb");
}

/**
 * @brief Swap the top two nodes of the stack A and B
 * @param a Stack A
 * @param b Stack B
 * @param op_list List of operations needed to sort the stacks
 */
void	ss(t_stack *a, t_stack *b, t_operation **op_list)
{
	swap(a);
	swap(b);
	add_operation(op_list, "ss");
}
