/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:52 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/19 19:38:53 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "push_swap.h"

static void	choose_sorting_algorithm(t_program_data *data);
static void	optimize_and_print_operations(t_program_data *data);

/**
 * @brief Chooses the sorting algorithm based on the number of elements.
 * @param data Program data.(All the data needed for the program)
 */
static void	choose_sorting_algorithm(t_program_data *data)
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

/**
 * @brief Optimizes and prints the operations.
 * @param data Program data.(All the data needed for the program)
 */
static void	optimize_and_print_operations(t_program_data *data)
{
	optimize_operations(&data->op_list);
	print_operations(data->op_list);
}

/**
 * @brief Main function for the push_swap program.
 */
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
	if (is_sorted_and_b_empty(data.stack_a, data.stack_b))
	{
		cleanup(&data);
		return (0);
	}
	choose_sorting_algorithm(&data);
	optimize_and_print_operations(&data);
	cleanup(&data);
	return (0);
}
