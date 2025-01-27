/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:13:16 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/27 23:40:15 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"

// pa: pop from B and push into A
void    pa(t_stack *a, t_stack *b)
{
    t_node *temp;

    if (!b || b->size == 0)
        return;

    temp = b->top;
    b->top = b->top->next;
    if (b->top)
        b->top->prev = NULL;
    else
        b->bottom = NULL;

    b->size--;

    // Вставляем узел temp поверх a
    temp->next = a->top;
    temp->prev = NULL;

    if (a->size == 0)
        a->bottom = temp;
    else
        a->top->prev = temp;

    a->top = temp;
    a->size++;

    ft_printf("pa\n");
}

// pb: pop from A and push into B
void    pb(t_stack *a, t_stack *b)
{
    t_node *temp;

    if (!a || a->size == 0)
        return;

    // 1) "Вырезаем" узел из вершины a
    temp = a->top;
    a->top = a->top->next;         // Сдвигаем вершину
    if (a->top)
        a->top->prev = NULL;
    else
        a->bottom = NULL;         // Если стек стал пуст

    a->size--;

    // 2) "Пришиваем" узел temp поверх стека b
    temp->next = b->top;
    temp->prev = NULL;

    if (b->size == 0)
        b->bottom = temp;
    else
        b->top->prev = temp;

    b->top = temp;
    b->size++;

    ft_printf("pb\n");
}
