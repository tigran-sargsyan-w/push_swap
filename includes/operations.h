/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:08:21 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 17:36:50 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "stack.h"

typedef struct s_operation
{
	char				*op;
	struct s_operation	*next;
}						t_operation;

void					sa(t_stack *a, t_operation **op_list);
void					sb(t_stack *b, t_operation **op_list);
void					ss(t_stack *a, t_stack *b, t_operation **op_list);
void					pa(t_stack *a, t_stack *b, t_operation **op_list);
void					pb(t_stack *a, t_stack *b, t_operation **op_list);
void					ra(t_stack *a, t_operation **op_list);
void					rb(t_stack *b, t_operation **op_list);
void					rr(t_stack *a, t_stack *b, t_operation **op_list);
void					rra(t_stack *a, t_operation **op_list);
void					rrb(t_stack *b, t_operation **op_list);
void					rrr(t_stack *a, t_stack *b, t_operation **op_list);

#endif
