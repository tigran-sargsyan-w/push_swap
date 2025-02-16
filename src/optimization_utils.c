/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:33:44 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/16 21:44:58 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "operations.h"

static int	has_pairs(const char *op1, const char *op2, char *ref1, char *ref2);
static int	is_cancelable(const char *op1, const char *op2);
static void	merge_operations(t_operation *curr, const char *new_op);

/**
 * @brief Checks if two operations match a given reference pair, 
 * regardless of order.
 * @param op1 First operation to compare.
 * @param op2 Second operation to compare.
 * @param ref1 First reference operation.
 * @param ref2 Second reference operation.
 * @return 1 if the operations match the reference pair, 0 otherwise.
 */
static int	has_pairs(const char *op1, const char *op2, char *ref1, char *ref2)
{
	if (ft_strcmp(op1, ref1) == 0 && ft_strcmp(op2, ref2) == 0)
		return (1);
	if (ft_strcmp(op1, ref2) == 0 && ft_strcmp(op2, ref1) == 0)
		return (1);
	return (0);
}

/**
 * @brief Checks if two operations can be canceled out.
 * @param op1 First operation to compare.
 * @param op2 Second operation to compare.
 * @return 1 if the operations can be canceled out, 0 otherwise.
 */
static int	is_cancelable(const char *op1, const char *op2)
{
	if (has_pairs(op1, op2, "ra", "rra"))
		return (1);
	if (has_pairs(op1, op2, "rb", "rrb"))
		return (1);
	if (has_pairs(op1, op2, "pa", "pb"))
		return (1);
	if (has_pairs(op1, op2, "rr", "rrr"))
		return (1);
	return (0);
}

/**
 * @brief Merges two operations into a single operation.
 * @param curr Current operation node.
 * @param new_op New operation to replace the current pair.
 */
static void	merge_operations(t_operation *curr, const char *new_op)
{
	t_operation	*temp;

	temp = curr->next;
	free(curr->op);
	curr->op = ft_strdup(new_op);
	curr->next = temp->next;
	free(temp->op);
	free(temp);
}

/**
 * @brief Attempts to cancel out a pair of operations.
 * @param prev Pointer to the previous operation node.
 * @return 1 if the operations were canceled, 0 otherwise.
 */
int	try_cancel_operations(t_operation **prev)
{
	t_operation	*curr;
	t_operation	*temp;

	curr = (*prev)->next;
	if (!curr || !curr->next)
		return (0);
	if (is_cancelable(curr->op, curr->next->op))
	{
		temp = curr->next;
		(*prev)->next = temp->next;
		free(curr->op);
		free(curr);
		free(temp->op);
		free(temp);
		return (1);
	}
	return (0);
}

/**
 * @brief Attempts to merge a pair of operations.
 * @param curr Current operation node.
 * @return 1 if the operations were merged, 0 otherwise.
 */
int	try_merge_operations(t_operation *curr)
{
	if (has_pairs(curr->op, curr->next->op, "ra", "rb"))
	{
		merge_operations(curr, "rr");
		return (1);
	}
	if (has_pairs(curr->op, curr->next->op, "rra", "rrb"))
	{
		merge_operations(curr, "rrr");
		return (1);
	}
	if (has_pairs(curr->op, curr->next->op, "sa", "sb"))
	{
		merge_operations(curr, "ss");
		return (1);
	}
	return (0);
}
