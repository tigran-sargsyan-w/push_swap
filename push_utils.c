/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:13:16 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/31 21:03:39 by tsargsya         ###   ########.fr       */
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

    // 1) "cut" the top node from stack a
    temp = a->top;
    a->top = a->top->next;
    if (a->top)
        a->top->prev = NULL;
    else
        a->bottom = NULL;

    a->size--;

    // 2) "paste" the top node to stack b
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
