/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:11 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/09 13:53:32 by tsargsya         ###   ########.fr       */
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

typedef struct s_operation
{
	char				*op;
	struct s_operation	*next;
}						t_operation;

// Stack functions
t_stack					*stack_init(void);
void					stack_push_initial(t_stack *stack, int value);
void					stack_clear(t_stack *stack);
void					print_stack_values(t_stack *stack);
void					print_stack_indices(t_stack *stack);

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

// Sorting
void					assign_sorted_indices(t_stack *a);
int						determine_chunks(int size);
void					dynamic_chunk_sort(t_stack *a, t_stack *b,
							int total_size, t_operation **op_list);
void					get_dynamic_chunk_limits(t_stack *a, int chunk_size,
							int *min, int *max);
t_node					*find_closest(t_stack *stack, int min, int max,
							int *moves, int *direction);
void					move_to_top_stack_a(t_stack *a, int direction,
							int moves, t_operation **op_list);
int						get_chunk_size(int size, int chunks);
int						determine_dynamic_chunks(int size);

// Operations
void					add_operation(t_operation **head, const char *op);
void					free_operations(t_operation *head);
void					print_operations(t_operation *head);
void					optimize_operations(t_operation **head);
int						try_merge_operations(t_operation *curr);
int						try_cancel_operations(t_operation **prev);

#endif