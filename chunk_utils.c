/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:48:42 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/09 13:59:09 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

// Функция для определения размера чанка
int	get_chunk_size(int size, int chunks)
{
	return ((size + chunks - 1) / chunks);
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
