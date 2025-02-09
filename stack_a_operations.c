/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_a_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:46:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/09 13:58:53 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

/**
 * @brief Finds the closest node in the stack whose index is within [min, max].
 * @param stack Pointer to the stack.
 * @param min Minimum index value of the chunk.
 * @param max Maximum index value of the chunk.
 * @param closest_pos Output parameter to store the 0-based position 
 * of the found node.
 * @return Pointer to the closest node in the chunk, or NULL if none found.
 */
t_node	*find_closest_in_chunk(t_stack *stack, int min, int max,
		int *closest_pos)
{
	t_node	*current;
	t_node	*closest;
	int		pos;

	current = stack->top;
	closest = NULL;
	pos = 0;
	*closest_pos = stack->size;
	while (current)
	{
		if (current->index >= min && current->index <= max)
		{
			if (pos < *closest_pos)
			{
				closest = current;
				*closest_pos = pos;
			}
		}
		current = current->next;
		pos = pos + 1;
	}
	return (closest);
}

/**
 * @brief Determines rotation parameters for the found node.
 * @param stack_size The total number of elements in the stack.
 * @param closest_pos The position of the found node.
 * @param direction Output parameter: set to 1 for upward rotation (ra,
		rb) or 2 for downward (rra, rrb).
 * @param moves Output parameter: number of moves required.
 */
void	set_rotation_params(int stack_size, int closest_pos, int *direction,
		int *moves)
{
	if (closest_pos <= stack_size / 2)
	{
		*direction = 1;
		*moves = closest_pos;
	}
	else
	{
		*direction = 2;
		*moves = stack_size - closest_pos;
	}
}

/**
 * @brief Finds the closest node within the specified chunk and 
 * computes rotation parameters.
 * @param stack Pointer to the stack.
 * @param min Minimum index value of the chunk.
 * @param max Maximum index value of the chunk.
 * @param moves Output parameter: number of moves required to bring 
 * the node to the top.
 * @param direction Output parameter: rotation direction (1 for ra,
 * rb; 2 for rra, rrb).
 * @return Pointer to the closest node in the chunk, or NULL if not found.
 */
t_node	*find_closest(t_stack *stack, int min, int max, int *moves,
		int *direction)
{
	int		closest_pos;
	t_node	*closest;

	closest = find_closest_in_chunk(stack, min, max, &closest_pos);
	if (closest)
	{
		set_rotation_params(stack->size, closest_pos, direction, moves);
	}
	return (closest);
}

// Функция для перемещения элемента на вершину
void	move_to_top_stack_a(t_stack *a, int direction, int moves,
		t_operation **op_list)
{
	if (direction == 1)
	{
		while (moves--)
			ra(a, op_list);
	}
	else
	{
		while (moves--)
			rra(a, op_list);
	}
}
