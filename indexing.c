/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:57:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/14 20:00:45 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

static int	find_min_unindexed_value(t_stack *stack);
static void	init_stack_indices(t_stack *stack);
static int	has_unindexed_elements(t_stack *stack);

/**
 * @brief Find the minimum value in the stack that does not have an index
 * @param stack where to search
 * @return Minimum value
 */
static int	find_min_unindexed_value(t_stack *stack)
{
	t_node	*current;
	int		min;
	int		found;

	current = stack->top;
	found = 0;
	while (current)
	{
		if (current->index == -1)
		{
			if (!found || current->value < min)
			{
				min = current->value;
				found = 1;
			}
		}
		current = current->next;
	}
	if (!found)
		return (INT_MAX);
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
 * @brief Check if there are unindexed elements in the stack
 * @param stack to check
 * @return 1 if there are unindexed elements, 0 otherwise
 */
static int	has_unindexed_elements(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (current)
	{
		if (current->index == -1)
			return (1);
		current = current->next;
	}
	return (0);
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
		if (!has_unindexed_elements(stack))
			exit(EXIT_FAILURE);
		min = find_min_unindexed_value(stack);
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
