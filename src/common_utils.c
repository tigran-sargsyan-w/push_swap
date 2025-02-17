/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:20:44 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/17 20:20:51 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "parsing.h"
#include "validation.h"
#include "optimization.h"

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
