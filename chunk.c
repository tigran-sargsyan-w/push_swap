/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:54:28 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/31 17:13:23 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>
#include "libft/ft_printf.h"


int determine_chunks(int size)
{
    if (size <= 20)
        return 2; // Меньше количество чанков для небольших стэков
    else if (size <= 100)
        return 5; // Для средних стэков
    else if (size <= 500)
        return 11; // Для больших стэков
    else
        return size / 50; // Пример для очень больших стэков
}

// Функция для определения размера чанка
int get_chunk_size(int size, int chunks)
{
    // return size / chunks + (size % chunks != 0 ? 1 : 0);
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
t_node *find_closest(t_stack *a, int min, int max, int *moves, int *direction)
{
    t_node *current = a->top;
    t_node *closest = NULL;
    int pos = 0;
    int closest_pos = a->size;
    
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
        if (closest_pos <= a->size / 2)
        {
            *direction = 1; // ra
            *moves = closest_pos;
        }
        else
        {
            *direction = 2; // rra
            *moves = a->size - closest_pos;
        }
    }
    return closest;
}

// Функция для перемещения элемента на вершину
void move_to_top(t_stack *a, int direction, int moves)
{
    if (direction == 1)
    {
        while (moves--) // check if top of B is < than middle of chunk => do rr and not ra //TODO  Smt like 146
            ra(a);
    }
    else
    {
        while (moves--)
            rra(a);
    }
}

void rotate_to_max(t_stack *b)
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
void chunk_sort(t_stack *a, t_stack *b, int size, int chunks)
{
    int chunk_size = get_chunk_size(size, chunks);
    
    for (int chunk = 0; chunk < chunks; chunk++)
    {
        int min, max;
        get_chunk_limits(chunk, chunk_size, size, &min, &max);
        
        while (1)
        {
            int direction, moves;
            t_node *target = find_closest(a, min, max, &moves, &direction);
            if (!target)
                break;
            
            
            move_to_top(a, direction, moves);
            pb(a, b);
            
            
            // Опционально: оптимизируем порядок в b
            if (b->size > 1 && b->top->index < (min + max) / 2)
                rb(b);
            else if (b->size > 1 && b->top->index < b->top->next->index)
                sb(b);
        }
    }
    
    // Возвращаем все элементы из b обратно в a
    while (b->size > 0)
    {
        rotate_to_max(b);
        pa(a, b);
    }    

}

