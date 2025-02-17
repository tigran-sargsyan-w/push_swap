/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 00:45:21 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/17 11:57:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "stack.h"
#include "ft_printf.h"

/**
 * @brief Initialize a new stack
 * @return Pointer to the new stack
 */
t_stack	*stack_init(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		exit(EXIT_FAILURE);
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	return (stack);
}

/**
 * @brief Add a new node to the top of the stack
 * @param stack stack to add the node to
 * @param value value to add to the stack
 * @details The index of the initial node is set to -1
 */
void	stack_push_initial(t_stack *stack, int value)
{
	t_node	*new_node;

	if (!stack)
		return ;
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->value = value;
	new_node->index = -1;
	new_node->next = stack->top;
	new_node->prev = NULL;
	if (stack->top)
		stack->top->prev = new_node;
	stack->top = new_node;
	if (stack->size == 0)
		stack->bottom = new_node;
	stack->size++;
}

/**
 * @brief Clears and frees the entire stack
 * @param stack stack to clear
 */
void	stack_clear(t_stack *stack)
{
	t_node	*temp;

	if (!stack)
		return ;
	while (stack->top)
	{
		temp = stack->top;
		stack->top = stack->top->next;
		free(temp);
	}
	free(stack);
}

/**
 * @brief Print the stack element values
 * @param stack stack to print
 */
void	print_stack_values(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	ft_printf("Stack: ");
	while (current)
	{
		ft_printf("%d ", current->value);
		current = current->next;
	}
	ft_printf("\n");
}

/**
 * @brief Print the stack element indices
 * @param stack stack to print
 */
void	print_stack_indices(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	ft_printf("Index: ");
	while (current)
	{
		ft_printf("%d ", current->index);
		current = current->next;
	}
	ft_printf("\n");
}
