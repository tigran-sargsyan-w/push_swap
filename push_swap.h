/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:11 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/02 17:47:40 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_node
{
	int					value;
	int					index;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_stack
{
	t_node				*top;
	t_node				*bottom;
	int					size;
}						t_stack;

typedef struct s_rotation
{
	int					count;
	int					direction;
}						t_rotation;

typedef struct s_operation
{
	char				*op;
	struct s_operation	*next;
}						t_operation;

// Stack functions
t_stack					*stack_init(void);
void					stack_push(t_stack *stack, int value);
int						stack_pop(t_stack *stack);
int						stack_peek(t_stack *stack);
int						stack_is_empty(t_stack *stack);
void					stack_clear(t_stack *stack);

// Operations push_swap
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

// Utils
void					print_stack(t_stack *stack);
void					print_stack_index(t_stack *stack);

// Sorting
void					assign_sorted_indices(t_stack *a);
int						determine_chunks(int size);
void					dynamic_chunk_sort(t_stack *a, t_stack *b,
							int total_size, t_operation **op_list);

// Operations
void					add_operation(t_operation **head, const char *op);
void					optimize_operations(t_operation **head);
void					print_operations(t_operation *head);
void					free_operations(t_operation *head);

#endif