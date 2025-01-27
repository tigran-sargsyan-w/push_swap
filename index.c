/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:57:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/27 20:59:58 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// find the minimum value in the stack that does not have an index
int find_min(t_stack *a)
{
    t_node *current;
    int min = INT_MAX;

    current = a->top;
    while (current)
    {
        if (current->index == -1 && current->value < min)
            min = current->value;
        current = current->next;
    }
    return min;
}

// Функция для присвоения индексов
void index_sort(t_stack *a)
{
    int index = 0;
    int min;

    // Инициализируем индексы как -1
    t_node *current = a->top;
    while (current)
    {
        current->index = -1;
        current = current->next;
    }

    // Присваиваем индексы от 0 до size-1
    while (index < a->size)
    {
        min = find_min(a);
        if (min == INT_MAX)
        {
            fprintf(stderr, "Error: Failed to find minimum during indexing\n");
            exit(EXIT_FAILURE);
        }
        // Присваиваем индекс первому встретившемуся минимальному значению
        current = a->top;
        while (current)
        {
            if (current->value == min && current->index == -1)
            {
                current->index = index;
                break;
            }
            current = current->next;
        }
        index++;
    }
}