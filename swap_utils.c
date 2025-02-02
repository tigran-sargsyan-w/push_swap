/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:10:03 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/02 18:54:43 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"

// swap the top two nodes of the stack
void	swap(t_stack *stack)
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

// Swap A
void	sa(t_stack *a, t_operation **op_list)
{
	swap(a);
	add_operation(op_list, "sa");
}

// Swap B
void	sb(t_stack *b, t_operation **op_list)
{
	swap(b);
	add_operation(op_list, "sb");
}

// Swap A и B
void	ss(t_stack *a, t_stack *b, t_operation **op_list)
{
	swap(a);
	swap(b);
	add_operation(op_list, "ss");
}
