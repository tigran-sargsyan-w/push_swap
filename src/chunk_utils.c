/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:48:42 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/16 21:13:32 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "stack.h"

static void	sort_int_array(int *arr, int size);

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

/**
 * @brief Determines the size of each chunk.
 * @param size The total number of elements.
 * @param chunks The number of chunks.
 * @return The size of each chunk.
 */
int	determine_chunk_size(int size, int chunks)
{
	return ((size + chunks - 1) / chunks);
}

/**
 * @brief Determines the number of chunks based on the number of elements.
 * @param size The total number of elements.
 * @return The number of chunks.
 */
int	determine_chunks_count(int size)
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
 * @brief Determines the limits of the current chunk.
 * @param a Pointer to stack A.
 * @param chunk_size The size of the current chunk.
 * @param min Output parameter to store the minimum index of the chunk.
 * @param max Output parameter to store the maximum index of the chunk.
 */
void	determine_chunk_limits(t_stack *a, int chunk_size, int *min, int *max)
{
	int		i;
	int		size;
	int		*indices;
	t_node	*current;

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
