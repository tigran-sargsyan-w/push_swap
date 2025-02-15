/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:09:11 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 20:30:05 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "operations.h"
# include "stack.h"

typedef struct s_program_data
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_operation	*op_list;
	char		**new_argv;
	int			argc;
	int			was_split;
}				t_program_data;

char			**split_in_quotes_args(int *argc, char **argv);
void			free_arguments(char **argv, int argc, int was_split);
void			parse_and_push_args(t_stack *stack, int argc, char **argv);
void			cleanup(t_program_data *data);

#endif
