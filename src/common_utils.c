/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:20:44 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/19 19:36:17 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "parsing.h"
#include "validation.h"
#include "optimization.h"

/**
 * @brief Check if the stack A is sorted and the stack B is empty
 * @param a The stack A
 * @param b The stack B
 * @return 1 if the stack A is sorted and the stack B is empty, 0 otherwise
 */
int	is_sorted_and_b_empty(t_stack *a, t_stack *b)
{
	t_node	*curr;

	if (b->size != 0)
		return (0);
	curr = a->top;
	while (curr && curr->next)
	{
		if (curr->value > curr->next->value)
			return (0);
		curr = curr->next;
	}
	return (1);
}

/**
 * @brief Parses and validates the arguments.
 * @param data Program data.(All the data needed for the program)
 * @param argv Array of arguments.
 * @return New argv array.
 */
char	**parse_and_validate_args(t_program_data *data, char **argv)
{
	data->was_split = (data->argc == 2);
	data->new_argv = split_in_quotes_args(&data->argc, argv);
	check_no_args(data->argc, data);
	check_numeric_args(data->argc, data->new_argv, data);
	check_int_limits_args(data->argc, data->new_argv, data);
	check_duplicates_args(data->argc, data->new_argv, data);
	return (data->new_argv);
}

/**
 * @brief Frees the allocated memory.
 * @param data Program data.(All the data needed for the program)
 */
void	cleanup(t_program_data *data)
{
	stack_clear(data->stack_a);
	stack_clear(data->stack_b);
	free_operations(data->op_list);
	free_arguments(data->new_argv, data->argc, data->was_split);
}
