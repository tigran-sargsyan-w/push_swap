/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:15:53 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/17 20:15:56 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "push_swap.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Check if the stack A is sorted and the stack B is empty
 * @param a The stack A
 * @param b The stack B
 * @return 1 if the stack A is sorted and the stack B is empty, 0 otherwise
 */
static int	is_sorted_and_b_empty(t_stack *a, t_stack *b)
{
	t_node	*curr;

	if (b->size != 0)
		return (0);
	curr = a->top;
	while (curr && curr->next)
	{
		if (curr->value > curr->next->value)
			return (0);
		curr = curr->next;
	}
	return (1);
}

/**
 * @brief Apply the swap and push operations
 * @param line The operation to apply
 * @param a The stack A
 * @param b The stack B
 * @param op_list The list of operations
 * @return 1 if the operation was applied, 0 otherwise
 */
static int	do_swap_push(char *line, t_stack *a, t_stack *b,
		t_operation **op_list)
{
	if (ft_strcmp(line, "sa") == 0)
		sa(a, op_list);
	else if (ft_strcmp(line, "sb") == 0)
		sb(b, op_list);
	else if (ft_strcmp(line, "ss") == 0)
		ss(a, b, op_list);
	else if (ft_strcmp(line, "pa") == 0)
		pa(a, b, op_list);
	else if (ft_strcmp(line, "pb") == 0)
		pb(a, b, op_list);
	else
		return (0);
	return (1);
}

/**
 * @brief Apply the rotate and reverse rotate operations
 * @param line The operation to apply
 * @param a The stack A
 * @param b The stack B
 * @param op_list The list of operations
 * @return 1 if the operation was applied, 0 otherwise
 */
static int	do_rotate(char *line, t_stack *a, t_stack *b, t_operation **op_list)
{
	if (ft_strcmp(line, "ra") == 0)
		ra(a, op_list);
	else if (ft_strcmp(line, "rb") == 0)
		rb(b, op_list);
	else if (ft_strcmp(line, "rr") == 0)
		rr(a, b, op_list);
	else if (ft_strcmp(line, "rra") == 0)
		rra(a, op_list);
	else if (ft_strcmp(line, "rrb") == 0)
		rrb(b, op_list);
	else if (ft_strcmp(line, "rrr") == 0)
		rrr(a, b, op_list);
	else
		return (0);
	return (1);
}

/**
 * @brief Process the input and apply the operations
 * @param data The program data
 */
static void	process_input_and_apply(t_program_data *data)
{
	char	*line;
	size_t	len;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!do_swap_push(line, data->stack_a, data->stack_b, &data->op_list)
			&& !do_rotate(line, data->stack_a, data->stack_b, &data->op_list))
		{
			ft_printf("Error\n");
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

/**
 * @brief Main function for the checker program
 */
int	main(int argc, char **argv)
{
	t_program_data	data;

	data.argc = argc;
	data.stack_a = stack_init();
	data.stack_b = stack_init();
	data.op_list = NULL;
	data.was_split = 0;
	data.new_argv = parse_and_validate_args(&data, argv);
	parse_and_push_args(data.stack_a, data.argc, data.new_argv);
	assign_sorted_indices(data.stack_a);
	process_input_and_apply(&data);
	if (is_sorted_and_b_empty(data.stack_a, data.stack_b))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	cleanup(&data);
	return (0);
}
