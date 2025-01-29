/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 00:45:21 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/29 15:56:55 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"
#include <stdlib.h>

// initialize a new stack
t_stack	*stack_init(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
	{
		// ft_printf("Failed to initialize stack\n");
		exit(EXIT_FAILURE);
	}
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	return (stack);
}
// add a new node to the top of the stack
void	stack_push(t_stack *stack, int value)
{
	t_node	*new_node;

	if (!stack)
		return ;
	new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		// ft_printf("Failed to push node to stack\n");
		exit(EXIT_FAILURE);
	}
	new_node->value = value;
	new_node->index = -1;
	new_node->next = stack->top;
	new_node->prev = NULL;
	if (stack->top)
		stack->top->prev = new_node;
	stack->top = new_node;
	if (stack->size == 0)
		stack->bottom = new_node;
	stack->size++;
}
// remove the top node from the stack and return its value
int	stack_pop(t_stack *stack)
{
	t_node	*temp;
	int		value;

	if (!stack || stack->size == 0)
		return (0); // Или обработка ошибки
	temp = stack->top;
	value = temp->value;
	stack->top = stack->top->next;
	if (stack->top)
		stack->top->prev = NULL;
	else
		stack->bottom = NULL; // Стек стал пустым
	free(temp);
	stack->size--;
	return (value);
}
// look at the top node of the stack without removing it
int	stack_peek(t_stack *stack)
{
	if (!stack || stack->size == 0)
		return (0); // Или обработка ошибки
	return (stack->top->value);
}
// check if the stack is empty
int	stack_is_empty(t_stack *stack)
{
	if (!stack)
		return (1);
	return (stack->size == 0);
}
// remove all nodes from the stack
void	stack_clear(t_stack *stack)
{
	t_node	*temp;

	if (!stack)
		return ;
	while (stack->top)
	{
		temp = stack->top;
		stack->top = stack->top->next;
		free(temp);
	}
	free(stack);
}

// update positions of the stack
void update_positions(t_stack *stack)
{
    t_node *current;
    int pos = 0;

    if (!stack)
        return;
    current = stack->top;
    while (current)
    {
        current->position = pos;
        pos++;
        current = current->next;
    }
}


// print the stack
void	print_stack(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	ft_printf("Stack (size=%d): ", stack->size);
	while (current)
	{
		ft_printf("%d ", current->value);
		current = current->next;
	}
	ft_printf("\n");
}

// print the stack
void	print_stack_index(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	ft_printf("Indexes (size=%d): ", stack->size);
	while (current)
	{
		ft_printf("%d ", current->index);
		current = current->next;
	}
	ft_printf("\n");
}

// print the stack
void	print_stack_position(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	ft_printf("Position (size=%d): ", stack->size);
	while (current)
	{
		ft_printf("%d ", current->position);
		current = current->next;
	}
	ft_printf("\n");
}
