/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:52 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/11 22:22:01 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

int	is_valid_digit_string(char *str)
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

void	check_no_args(int argc)
{
	if (argc == 1)
	{
		ft_printf("Error: no arguments\n");
		exit(EXIT_FAILURE);
	}
}

void	check_numeric_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_digit_string(argv[i]))
		{
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_int_limits_args(int argc, char **argv)
{
	int		i;
	long	num;

	i = 1;
	num = 0;
	while (i < argc)
	{
		num = ft_atol(argv[i]);
		if (num < INT_MIN || num > INT_MAX)
		{
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_duplicates_args(int argc, char **argv)
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

void	parse_and_push_args(t_stack *stack_a, int argc, char **argv)
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

char	**split_and_count(char *arg, int *count)
{
	char	**split_args;

	split_args = ft_split(arg, ' ');
	if (!split_args)
	{
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	*count = 0;
	while (split_args[*count])
		(*count)++;
	return (split_args);
}

char	**construct_new_argv(char **split_args, int count, char **argv,
		int *argc)
{
	char	**new_argv;
	int		i;

	new_argv = (char **)malloc((count + 2) * sizeof(char *));
	if (!new_argv)
	{
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	new_argv[0] = argv[0];
	i = 0;
	while (i < count)
	{
		new_argv[i + 1] = split_args[i];
		i++;
	}
	new_argv[i + 1] = NULL;
	*argc = count + 1;
	free(split_args);
	return (new_argv);
}

char	**split_if_single_arg(int *argc, char **argv)
{
	char	**split_args;
	int		count;

	if (*argc == 2)
	{
		split_args = split_and_count(argv[1], &count);
		return (construct_new_argv(split_args, count, argv, argc));
	}
	return (argv);
}

void	free_arguments(char **argv, int argc, int was_split)
{
	int	i;

	i = 1;
	if (was_split)
	{
		while (i < argc)
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
}

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_operation	*op_list;
	int			was_split;
	char		**new_argv;

	was_split = (argc == 2);
	new_argv = split_if_single_arg(&argc, argv);
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
