/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:39:51 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 13:30:30 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>

static int	is_valid_digit_string(char *str);

static int	is_valid_digit_string(char *str)
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

void	check_no_args(int argc, t_program_data *data)
{
	if (argc == 1)
	{
		cleanup(data);
		ft_printf("Error: no arguments\n");
		exit(EXIT_FAILURE);
	}
}

void	check_numeric_args(int argc, char **argv, t_program_data *data)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_digit_string(argv[i]))
		{
			cleanup(data);
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_int_limits_args(int argc, char **argv, t_program_data *data)
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
			cleanup(data);
			ft_printf("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	check_duplicates_args(int argc, char **argv, t_program_data *data)
{
	int	i;
	int	j;
	int	num;
	int	num2;

	i = 1;
	while (i < argc)
	{
		j = 1;
		num = ft_atoi(argv[i]);
		while (j < argc)
		{
			num2 = ft_atoi(argv[j]);
			if (num == num2 && i != j)
			{
				cleanup(data);
				ft_printf("Error\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}
