/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:57:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/04 23:58:50 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

static int	find_min_unindexed_value(t_stack *stack);
static void	init_stack_indices(t_stack *stack);

/**
 * @brief Find the minimum value in the stack that does not have an index
 * @param stack where to search
 * @return Minimum value
 */
static int	find_min_unindexed_value(t_stack *stack)
{
	t_node	*current;
	int		min;

	min = INT_MAX;
	current = stack->top;
	while (current)
	{
		if (current->index == -1 && current->value < min)
			min = current->value;
		current = current->next;
	}
	return (min);
}

/**
 * @brief Initialize the indices of the stack elements
 * @param stack to initialize
 */
static void	init_stack_indices(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (current)
	{
		current->index = -1;
		current = current->next;
	}
}

/**
 * @brief Assigns indices to the stack elements in ascending order
 * @param stack to assign indices to
 */
void	assign_sorted_indices(t_stack *stack)
{
	int		index;
	int		min;
	t_node	*current;

	index = 0;
	current = stack->top;
	init_stack_indices(stack);
	while (index < stack->size)
	{
		min = find_min_unindexed_value(stack);
		if (min == INT_MAX)
			exit(EXIT_FAILURE);
		current = stack->top;
		while (current)
		{
			if (current->value == min && current->index == -1)
			{
				current->index = index;
				break ;
			}
			current = current->next;
		}
		index++;
	}
}
