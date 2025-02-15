/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:53:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 21:24:58 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"
#include <stdlib.h>

/**
 * @brief Adds a new operation to the list.
 * @param op_list Pointer to the head of the operation list.
 * @param op Operation to add.
 */
void	add_operation(t_operation **op_list, const char *op)
{
	t_operation	*new_node;
	t_operation	*tmp;

	new_node = malloc(sizeof(t_operation));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->op = ft_strdup(op);
	if (!new_node->op)
		exit(EXIT_FAILURE);
	new_node->next = NULL;
	if (*op_list == NULL)
	{
		*op_list = new_node;
	}
	else
	{
		tmp = *op_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

/**
 * @brief Frees the operation list.
 * @param head Pointer to the head of the operation list.
 */
void	free_operations(t_operation *head)
{
	t_operation	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->op);
		free(tmp);
	}
}

/**
 * @brief Prints the operation list.
 * @param head Pointer to the head of the operation list.
 */
void	print_operations(t_operation *head)
{
	while (head)
	{
		ft_printf("%s\n", head->op);
		head = head->next;
	}
}

/**
 * @brief Optimizes the list by merging and canceling out operations.
 * @param head Pointer to the head of the operation list.
 */
void	optimize_operations(t_operation **head)
{
	t_operation	dummy;
	t_operation	*prev;

	prev = &dummy;
	dummy.next = *head;
	while (prev->next && prev->next->next)
	{
		if (try_merge_operations(prev->next) || try_cancel_operations(&prev))
			continue ;
		prev = prev->next;
	}
	*head = dummy.next;
}
