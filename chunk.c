/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:54:28 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/02 19:15:51 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>
#include "libft/ft_printf.h"
#include <stdlib.h>

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
void move_to_top_stack_a(t_stack *a, int direction, int moves, t_operation **op_list)
{
    if (direction == 1)
    {
        while (moves--) // check if top of B is < than middle of chunk => do rr and not ra
            ra(a, op_list);
    }
    else
    {
        while (moves--)
            rra(a, op_list);
    }
}

// Функция для оптимизации порядка в b
void rotate_to_max_stack_b(t_stack *b, t_operation **op_list)
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
int determine_dynamic_chunks(int size)
{
    int chunks;

    // Примерная логика:
    // Если осталось очень много элементов, используем меньше чанков (грубая сортировка).
    // Если элементов меньше, увеличиваем число чанков (точная доработка).
    if (size > 500)
        chunks = 7;
    else if (size > 100)
        chunks = 4;
    else if (size > 50)
        chunks = 3;
    else
        chunks = 2;

    return chunks;
}

// Функция сравнения для qsort (сортируем по возрастанию)
int cmp_int(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a - int_b);
}

// Функция для определения границ чанка динамически
void get_dynamic_chunk_limits(t_stack *a, int chunk_size, int *min, int *max)
{
    int size = a->size;
    if (size <= 0)
        return;

    // Выделяем память для массива индексов оставшихся элементов
    int *indices = malloc(sizeof(int) * size);
    if (!indices)
        return;

    // Заполняем массив значениями индексов из стека
    t_node *current = a->top;
    int i = 0;
    while (current)
    {
        indices[i++] = current->index;
        current = current->next;
    }

    // Сортируем массив индексов по возрастанию
    qsort(indices, size, sizeof(int), cmp_int);

    // Определяем границы: минимальное значение всегда самое маленькое,
    // максимальное — значение на позиции (chunk_size - 1) или последнее, если оставшихся элементов меньше chunk_size.
    *min = indices[0];
    if (chunk_size <= size)
        *max = indices[chunk_size - 1];
    else
        *max = indices[size - 1];

    free(indices);
}

// Функция для динамической сортировки чанков
void dynamic_chunk_sort(t_stack *a, t_stack *b, int total_size, t_operation **op_list)
{
    int chunk_count = 6;
    
    while (a->size > 0)
    {
        // Пересчитываем динамически количество чанков в зависимости от оставшихся элементов
        // Например, уменьшаем чанки, когда осталось меньше элементов
        if (a->size < total_size / 2)
        {
            chunk_count = determine_dynamic_chunks(a->size);
        }
        
        int chunk_size = get_chunk_size(a->size, chunk_count);
        // Можно использовать динамический алгоритм для определения границ:
        // Например, вычислить минимальное значение текущего диапазона по индексу и максимальное,
        // либо брать квантиль оставшихся элементов.
        int min_index, max_index;
        get_dynamic_chunk_limits(a, chunk_size, &min_index, &max_index);
        
        // Перемещаем элементы из A в B, которые попадают в текущий динамический чанк
        while (1)
        {
            int direction_a, moves_a;
            t_node *target_a = find_closest(a, min_index, max_index, &moves_a, &direction_a);
            if (!target_a)
                break;
            
            move_to_top_stack_a(a, direction_a, moves_a, op_list);
            pb(a, b, op_list);
            
            // Оптимизация порядка в B (например, можно доработать условие)
            if (b->size > 1 && b->top->index < (min_index + max_index) / 2)
            {
                rb(b, op_list);
            }
        }
        // Если необходимо, можно также сразу вернуть часть элементов из B в A, чтобы подготовить
        // их к финальной сортировке, или корректировать порядок в B.
    }
    
    // Return all elements from B to A
    while (b->size > 0)
    {
        rotate_to_max_stack_b(b, op_list);
        pa(a, b, op_list);
    }
}
