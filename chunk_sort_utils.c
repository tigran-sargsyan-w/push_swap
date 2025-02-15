/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:02 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 17:33:25 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/push_swap.h"
#include <stddef.h>

static t_node	*find_closest_in_chunk(t_stack *stack, int min, int max,
					int *closest_pos);
static void		set_rotation_params(int stack_size, int closest_pos,
					int *direction, int *moves);

/**
 * @brief Finds the closest node in the stack whose index is within [min, max].
 * @param stack Pointer to the stack.
 * @param min Minimum index value of the chunk.
 * @param max Maximum index value of the chunk.
 * @param closest_pos Output parameter to store the 0-based position 
 * of the found node.
 * @return Pointer to the closest node in the chunk, or NULL if none found.
 */
static t_node	*find_closest_in_chunk(t_stack *stack, int min, int max,
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
static void	set_rotation_params(int stack_size, int closest_pos, int *direction,
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
 * @param rot Output parameter to store the rotation parameters.
 * @return Pointer to the closest node in the chunk, or NULL if not found.
 */
t_node	*find_closest(t_stack *stack, int min, int max, t_rotation_params *rot)
{
	int		pos;
	t_node	*closest;

	closest = find_closest_in_chunk(stack, min, max, &pos);
	if (closest)
	{
		set_rotation_params(stack->size, pos, &rot->direction, &rot->moves);
	}
	return (closest);
}

/**
 * @brief Moves the node to the top of the stack.
 * @param a Pointer to the stack.
 * @param direction 1 for upward rotation (ra), 2 for downward (rra).
 * @param moves Number of moves required.
 * @param op_list Pointer to the list of operations.
 */
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
