/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:13:16 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 21:25:24 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

/**
 * @brief Pop from B and push into A
 * @param a stack A
 * @param b stack B
 * @param op_list list of operations needed to sort the stacks
 */
void	pa(t_stack *a, t_stack *b, t_operation **op_list)
{
	t_node	*temp;

	if (!b || b->size == 0)
		return ;
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
	add_operation(op_list, "pa");
}

/**
 * @brief Pop from A and push into B
 * @param a stack A
 * @param b stack B
 * @param op_list list of operations needed to sort the stacks
 */
void	pb(t_stack *a, t_stack *b, t_operation **op_list)
{
	t_node	*temp;

	if (!a || a->size == 0)
		return ;
	temp = a->top;
	a->top = a->top->next;
	if (a->top)
		a->top->prev = NULL;
	else
		a->bottom = NULL;
	a->size--;
	temp->next = b->top;
	temp->prev = NULL;
	if (b->size == 0)
		b->bottom = temp;
	else
		b->top->prev = temp;
	b->top = temp;
	b->size++;
	add_operation(op_list, "pb");
}
