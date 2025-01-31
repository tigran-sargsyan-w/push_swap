/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:54:28 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/31 20:34:41 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>
#include "libft/ft_printf.h"

// Функция для определения количества чанков
int determine_chunks(int size)
{
    if (size <= 20)
        return 2;
    else if (size <= 100)
        return 5;
    else if (size <= 500)
        return 11;
    else
        return size / 50;
}

// Функция для определения размера чанка
int get_chunk_size(int size, int chunks)
{
    return (size + chunks - 1) / chunks;
}

// Функция для определения границ чанка
void get_chunk_limits(int chunk, int chunk_size, int size, int *min, int *max)
{
    *min = chunk * chunk_size;
    *max = (chunk + 1) * chunk_size - 1;
    if (chunk == size / chunk_size)
        *max = size - 1;
}

// Функция для нахождения ближайшего элемента текущего чанка
t_node *find_closest(t_stack *stack, int min, int max, int *moves, int *direction)
{
    t_node *current = stack->top;
    t_node *closest = NULL;
    int pos = 0;
    int closest_pos = stack->size;
    
    // Поиск сверху
    while (current)
    {
        if (current->index >= min && current->index <= max)
        {
            if (pos < closest_pos)
            {
                closest = current;
                closest_pos = pos;
            }
        }
        current = current->next;
        pos++;
    }
    
    // Определение направления и количества вращений
    if (closest)
    {
        if (closest_pos <= stack->size / 2)
        {
            *direction = 1; // ra, rb
            *moves = closest_pos;
        }
        else
        {
            *direction = 2; // rra, rrb
            *moves = stack->size - closest_pos;
        }
    }
    return closest;
}

// Функция для перемещения элемента на вершину
void move_to_top_stack_a(t_stack *a, int direction, int moves)
{
    if (direction == 1)
    {
        while (moves--) // check if top of B is < than middle of chunk => do rr and not ra
            ra(a);
    }
    else
    {
        while (moves--)
            rra(a);
    }
}

// Функция для оптимизации порядка в b
void rotate_to_max_stack_b(t_stack *b)
{
    t_node *current = b->top;
    t_node *max = current;
    int pos = 0;
    int max_pos = 0;
    
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
    if (max_pos <= b->size / 2)
    {
        while (max_pos--)
            rb(b);
    }
    else
    {
        max_pos = b->size - max_pos;
        while (max_pos--)
            rrb(b);
    }
}

// Основная функция сортировки методом чанков
void chunk_sort(t_stack *a, t_stack *b, int size, int chunk_count)
{
    int chunk_size = get_chunk_size(size, chunk_count);
    
    int chunk = 0;
    while (chunk < chunk_count)
    {
        int min, max;
        get_chunk_limits(chunk, chunk_size, size, &min, &max);
        
        while (1)
        {
            int direction_a, moves_a;
            t_node *target_a = find_closest(a, min, max, &moves_a, &direction_a);
            if (!target_a)
                break;
            
            int direction_b, moves_b;
            t_node *target_b = find_closest(b, min, max, &moves_b, &direction_b);
    
            move_to_top_stack_a(a, direction_a, moves_a);
            pb(a, b);
            
            // Опционально: оптимизируем порядок в b
            if (b->size > 1 && b->top->index < (min + max) / 2)
            {
                rb(b);
            }
            else if (b->size > 1 && b->top->index < b->top->next->index)
            {
                sb(b);
            }
        }
        chunk++;
    }
    
    // Возвращаем все элементы из b обратно в a
    while (b->size > 0)
    {
        rotate_to_max_stack_b(b);
        pa(a, b);
    }
}
