/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:54:28 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/06 22:29:17 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"
#include <stddef.h>
#include <stdlib.h>

// Функция для определения размера чанка
int	get_chunk_size(int size, int chunks)
{
	return ((size + chunks - 1) / chunks);
}

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

// Функция для динамического определения количества чанков
int	determine_dynamic_chunks(int size)
{
	int	chunks;

	if (size > 500)
		chunks = 7;
	else if (size > 100)
		chunks = 4;
	else if (size > 50)
		chunks = 3;
	else
		chunks = 2;
	return (chunks);
}

/**
 * @brief Sorts an integer array in ascending order using bubble sort.
 * @param arr Pointer to the array of integers.
 * @param size The number of elements in the array.
 */
static void	sort_int_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j = j + 1;
		}
		i = i + 1;
	}
}

// Функция для определения границ чанка динамически
void	get_dynamic_chunk_limits(t_stack *a, int chunk_size, int *min, int *max)
{
	int		size;
	int		*indices;
	t_node	*current;
	int		i;

	size = a->size;
	if (size <= 0)
		return ;
	indices = malloc(sizeof(int) * size);
	if (!indices)
		return ;
	current = a->top;
	i = 0;
	while (current)
	{
		indices[i++] = current->index;
		current = current->next;
	}
	sort_int_array(indices, size);
	*min = indices[0];
	if (chunk_size <= size)
		*max = indices[chunk_size - 1];
	else
		*max = indices[size - 1];
	free(indices);
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
