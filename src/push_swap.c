/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:52 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 21:25:21 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

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

void	choose_sorting_algorithm(t_program_data *data)
{
	if (data->stack_a->size == 2
		&& data->stack_a->top->value > data->stack_a->top->next->value)
		sa(data->stack_a, &data->op_list);
	else if (data->stack_a->size == 3)
		sort_three(data->stack_a, &data->op_list);
	else if (data->stack_a->size == 4)
		sort_four(data->stack_a, data->stack_b, &data->op_list);
	else if (data->stack_a->size == 5)
		sort_five(data->stack_a, data->stack_b, &data->op_list);
	else
		dynamic_chunk_sort(data->stack_a, data->stack_b, data->stack_a->size,
			&data->op_list);
}

void	optimize_and_print_operations(t_program_data *data)
{
	optimize_operations(&data->op_list);
	print_operations(data->op_list);
}

void	cleanup(t_program_data *data)
{
	stack_clear(data->stack_a);
	stack_clear(data->stack_b);
	free_operations(data->op_list);
	free_arguments(data->new_argv, data->argc, data->was_split);
}

int	main(int argc, char **argv)
{
	t_program_data	data;

	data.argc = argc;
	data.stack_a = stack_init();
	data.stack_b = stack_init();
	data.op_list = NULL;
	data.new_argv = parse_and_validate_args(&data, argv);
	parse_and_push_args(data.stack_a, data.argc, data.new_argv);
	assign_sorted_indices(data.stack_a);
	choose_sorting_algorithm(&data);
	optimize_and_print_operations(&data);
	cleanup(&data);
	return (0);
}
