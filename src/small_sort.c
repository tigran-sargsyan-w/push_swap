/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:50:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 21:25:37 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_value(t_stack *stack);
static int	find_value_position(t_stack *stack, int value);

static int	find_min_value(t_stack *stack)
{
	t_node	*temp;
	int		min;

	temp = stack->top;
	min = temp->value;
	while (temp)
	{
		if (temp->value < min)
			min = temp->value;
		temp = temp->next;
	}
	return (min);
}

static int	find_value_position(t_stack *stack, int value)
{
	t_node	*temp;
	int		pos;

	temp = stack->top;
	pos = 0;
	while (temp)
	{
		if (temp->value == value)
			return (pos);
		pos++;
		temp = temp->next;
	}
	return (-1);
}

void	sort_three(t_stack *stack, t_operation **op_list)
{
	int	a;
	int	b;
	int	c;

	a = stack->top->value;
	b = stack->top->next->value;
	c = stack->bottom->value;
	if (a > b && b < c && a < c)
		sa(stack, op_list);
	else if (a > b && b > c)
	{
		sa(stack, op_list);
		rra(stack, op_list);
	}
	else if (a > b && b < c && a > c)
		ra(stack, op_list);
	else if (a < b && b > c && a < c)
	{
		sa(stack, op_list);
		ra(stack, op_list);
	}
	else if (a < b && b > c)
		rra(stack, op_list);
}

void	sort_four(t_stack *a, t_stack *b, t_operation **op_list)
{
	int	min;

	min = find_min_value(a);
	while (a->top->value != min)
	{
		if (find_value_position(a, min) < a->size / 2)
			ra(a, op_list);
		else
			rra(a, op_list);
	}
	pb(a, b, op_list);
	sort_three(a, op_list);
	pa(a, b, op_list);
}

void	sort_five(t_stack *a, t_stack *b, t_operation **op_list)
{
	int	min;

	while (a->size > 3)
	{
		min = find_min_value(a);
		while (a->top->value != min)
		{
			if (find_value_position(a, min) < a->size / 2)
				ra(a, op_list);
			else
				rra(a, op_list);
		}
		pb(a, b, op_list);
	}
	sort_three(a, op_list);
	pa(a, b, op_list);
	pa(a, b, op_list);
}
