/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:52 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/26 17:52:52 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

int	push_swap(int *arr)
{
	return (0);
}

int is_valid_number(char *str)
{
    int i = 0;
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


int	main(int argc, char **argv)
{
	t_stack *stack_a = stack_init();
	t_stack *stack_b = stack_init();
	
	if (argc == 1)
	{
		ft_printf("Error: no arguments\n");
		return (0);
	}
	
	int i = 1;
	int j = 1;
	int num = 0;
	int num2 = 0;
	
	while(i < argc)
	{
		if (!is_valid_number(argv[i])) // check if the argument is a valid number
		{
			ft_printf("Error\n");
			stack_clear(stack_a);
			stack_clear(stack_a);
			return (0);
		}
		i++;
	}
	i = 1;
	while (i < argc)
	{
		j = 1;
		num = ft_atoi(argv[i]);
		if (num < INT_MIN || num > INT_MAX) // check if the number is within the integer range
        {
            ft_printf("Error\n");
			stack_clear(stack_a);
			stack_clear(stack_a);
            return (0);
        }
		while (j < argc)
		{
			num2 = ft_atoi(argv[j]);
			if (num == num2 && i != j) // check if there are duplicate numbers
            {
                ft_printf("Error\n");
				stack_clear(stack_a);
        		stack_clear(stack_a);
                return (0);
            }
		}
		i++;
	}

	i = 1;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		stack_push(stack_a, num);
		i++;
	}
	

	print_stack(stack_a);
	
	ft_printf("Finish\n");// delete this line
	stack_clear(stack_a);
	stack_clear(stack_a);

	return (0);
}
