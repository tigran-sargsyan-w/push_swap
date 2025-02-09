/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:52 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/09 18:51:44 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	check_one_argument(int argc)
{
	if (argc == 1)
	{
		ft_printf("Error: no arguments\n");
		exit(EXIT_FAILURE);
	}
}

void	check_if_arguments_are_numbers(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_if_arg_within_int_limits(int argc, char **argv)
{
	int	i;
	int	num;

	i = 1;
	num = 0;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		if (num < INT_MIN || num > INT_MAX)
		{
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_if_there_are_duplicates(int argc, char **argv)
{
	int	i;
	int	j;
	int	num;
	int	num2;

	i = 1;
	j = 1;
	num = 0;
	num2 = 0;
	while (i < argc)
	{
		j = 1;
		num = ft_atoi(argv[i]);
		while (j < argc)
		{
			num2 = ft_atoi(argv[j]);
			if (num == num2 && i != j)
			{
				ft_printf("Error\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

void	parse_args_in_stack(t_stack *stack_a, int argc, char **argv)
{
	int	i;
	int	value;

	i = argc - 1;
	while (i >= 1)
	{
		value = ft_atoi(argv[i]);
		stack_push_initial(stack_a, value);
		i--;
	}
}

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_operation	*op_list;

	check_one_argument(argc);
	check_if_arguments_are_numbers(argc, argv);
	check_if_arg_within_int_limits(argc, argv);
	check_if_there_are_duplicates(argc, argv);
	stack_a = stack_init();
	stack_b = stack_init();
	op_list = NULL;
	parse_args_in_stack(stack_a, argc, argv);
	assign_sorted_indices(stack_a);
	// print_stack_values(stack_a);
	// print_stack_indices(stack_a);
	dynamic_chunk_sort(stack_a, stack_b, stack_a->size, &op_list);
	optimize_operations(&op_list);
	print_operations(op_list);
	// print_stack_values(stack_a);
	// print_stack_indices(stack_a);
	stack_clear(stack_a);
	stack_clear(stack_b);
	free_operations(op_list);
	return (0);
}
