/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:52:41 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 20:45:45 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"
#include "../libft/libft.h"
#include "../includes/push_swap.h"
#include <stdlib.h>

static char	**split_and_count(char *arg, int *count);
static char	**construct_new_argv(char **split_args, int count, char **argv,
				int *argc);

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
