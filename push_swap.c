/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:52 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/14 21:01:02 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_operation	*op_list;
	int			was_split;
	char		**new_argv;

	was_split = (argc == 2);
	new_argv = split_in_quotes_args(&argc, argv);
	check_no_args(argc);
	check_numeric_args(argc, new_argv);
	check_int_limits_args(argc, new_argv);
	check_duplicates_args(argc, new_argv);
	stack_a = stack_init();
	stack_b = stack_init();
	op_list = NULL;
	parse_and_push_args(stack_a, argc, new_argv);
	assign_sorted_indices(stack_a);
	// print_stack_values(stack_a);
	// print_stack_indices(stack_a);
	// dynamic_chunk_sort(stack_a, stack_b, stack_a->size, &op_list);
	if (stack_a->size == 2 && stack_a->top->value > stack_a->top->next->value)
		sa(stack_a, &op_list);
	else if (stack_a->size == 3)
		sort_three(stack_a, &op_list);
	else if (stack_a->size == 4)
		sort_four(stack_a, stack_b, &op_list);
	else if (stack_a->size == 5)
		sort_five(stack_a, stack_b, &op_list);
	else
		dynamic_chunk_sort(stack_a, stack_b, stack_a->size, &op_list);
	optimize_operations(&op_list);
	print_operations(op_list);
	// print_stack_values(stack_a);
	// print_stack_indices(stack_a);
	stack_clear(stack_a);
	stack_clear(stack_b);
	free_operations(op_list);
	free_arguments(new_argv, argc, was_split);
	return (0);
}
