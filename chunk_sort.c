/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:54:28 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/09 13:49:44 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Finds the position of the element with the maximum index in stack B.
 * @param b Pointer to stack B.
 * @return The position (0-based) of the element with the highest index.
 */
static int	find_max_pos_in_stack(t_stack *b)
{
	int		pos;
	int		max_pos;
	t_node	*current;
	t_node	*max;

	pos = 0;
	max_pos = 0;
	current = b->top;
	max = current;
	while (current)
	{
		if (current->index > max->index)
		{
			max = current;
			max_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (max_pos);
}

/**
 * @brief Rotates stack B so that the element with the maximum index
 * becomes the top.
 * @param b Pointer to stack B.
 * @param op_list Pointer to the operations list.
 * @details Depending on the position of the maximum element,
 *          the function rotates stack B upwards (rb) or downwards (rrb)
 *          to bring that element to the top.
 */
void	rotate_to_max_stack_b(t_stack *b, t_operation **op_list)
{
	int	max_pos;

	max_pos = find_max_pos_in_stack(b);
	if (max_pos <= b->size / 2)
	{
		while (max_pos--)
			rb(b, op_list);
	}
	else
	{
		max_pos = b->size - max_pos;
		while (max_pos--)
			rrb(b, op_list);
	}
}

/**
 * @brief Processes the current chunk by moving eligible elements
 * from stack A to stack B.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 * @param chunk_size The size of the current chunk.
 * @param op_list Pointer to the operations list.
 */
static void	process_current_chunk(t_stack *a, t_stack *b, int chunk_size,
		t_operation **op_list)
{
	t_node	*target;
	int		min_index;
	int		max_index;
	int		direction;
	int		moves;

	get_dynamic_chunk_limits(a, chunk_size, &min_index, &max_index);
	while (1)
	{
		target = find_closest(a, min_index, max_index, &moves, &direction);
		if (!target)
			break ;
		move_to_top_stack_a(a, direction, moves, op_list);
		pb(a, b, op_list);
		if (b->size > 1 && b->top->index < (min_index + max_index) / 2)
			rb(b, op_list);
	}
}

/**
 * @brief Returns all elements from stack B to stack A.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 * @param op_list Pointer to the operations list.
 */
static void	return_all_to_a(t_stack *a, t_stack *b, t_operation **op_list)
{
	while (b->size > 0)
	{
		rotate_to_max_stack_b(b, op_list);
		pa(a, b, op_list);
	}
}

/**
 * @brief Dynamically sorts stack A by processing it in chunks.
 * @param a Pointer to stack A.
 * @param b Pointer to stack B.
 * @param total_size The initial total number of elements in stack A.
 * @param op_list Pointer to the operations list.
 * @details The function computes a dynamic chunk size based 
 * on the current size of A,processes each chunk by moving 
 * eligible elements to stack B, and finally
 * returns all elements from B back to A.
 */
void	dynamic_chunk_sort(t_stack *a, t_stack *b, int total_size,
		t_operation **op_list)
{
	int	chunk_count;
	int	chunk_size;

	chunk_count = 6;
	while (a->size > 0)
	{
		if (a->size < total_size / 2)
			chunk_count = determine_dynamic_chunks(a->size);
		chunk_size = get_chunk_size(a->size, chunk_count);
		process_current_chunk(a, b, chunk_size, op_list);
	}
	return_all_to_a(a, b, op_list);
}
