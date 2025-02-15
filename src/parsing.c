/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:52:41 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 21:41:08 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "push_swap.h"
#include <stdlib.h>

static char	**split_and_count(char *arg, int *count);
static char	**construct_new_argv(char **split_args, int count, char **argv,
				int *argc);

/**
 * @brief Splits string into an array of strings and counts the
 * number of elements.
 * @param arg Argument string to split.
 * @param count Pointer to the variable to store the number of elements.
 * @return Array of strings.
 */
static char	**split_and_count(char *arg, int *count)
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

/**
 * @brief Constructs a new argv array with the split arguments.
 * @param split_args Array of split arguments.
 * @param count Number of split arguments.
 * @param argv Original argv array.
 * @param argc Pointer to the variable to store the number of arguments.
 * @return New argv array.
 */
static char	**construct_new_argv(char **split_args, int count, char **argv,
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

/**
 * @brief Parses and pushes arguments to the stack.
 * @param stack_a Stack to push the arguments to.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 */
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

/**
 * @brief Splits arguments in quotes and constructs a new argv array.
 * @param argc Pointer to the number of arguments.
 * @param argv Array of arguments.
 * @return New argv array.
 */
char	**split_in_quotes_args(int *argc, char **argv)
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

/**
 * @brief Frees the arguments array.
 * @param argv Array of arguments.
 * @param argc Number of arguments.
 * @param was_split Flag indicating if the arguments were split.
 */
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
