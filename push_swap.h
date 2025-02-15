/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:11 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 12:14:55 by tsargsya         ###   ########.fr       */
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

typedef struct s_rotation_params
{
	int					moves;
	int					direction;
}						t_rotation_params;

typedef struct s_program_data
{
	t_stack				*stack_a;
	t_stack				*stack_b;
	t_operation			*op_list;
	char				**new_argv;
	int					argc;
	int					was_split;
}						t_program_data;

// stack.c
t_stack					*stack_init(void);
void					stack_push_initial(t_stack *stack, int value);
void					stack_clear(t_stack *stack);
void					print_stack_values(t_stack *stack);
void					print_stack_indices(t_stack *stack);
// swap_utils.c
void					sa(t_stack *a, t_operation **op_list);
void					sb(t_stack *b, t_operation **op_list);
void					ss(t_stack *a, t_stack *b, t_operation **op_list);
// push_utils.c
void					pa(t_stack *a, t_stack *b, t_operation **op_list);
void					pb(t_stack *a, t_stack *b, t_operation **op_list);
// rotate_utils.c
void					ra(t_stack *a, t_operation **op_list);
void					rb(t_stack *b, t_operation **op_list);
void					rr(t_stack *a, t_stack *b, t_operation **op_list);
// reverse_rotate_utils.c
void					rra(t_stack *a, t_operation **op_list);
void					rrb(t_stack *b, t_operation **op_list);
void					rrr(t_stack *a, t_stack *b, t_operation **op_list);
// indexing.c
void					assign_sorted_indices(t_stack *a);
// small_sort.c
void					sort_three(t_stack *stack, t_operation **op_list);
void					sort_four(t_stack *a, t_stack *b,
							t_operation **op_list);
void					sort_five(t_stack *a, t_stack *b,
							t_operation **op_list);
// chunk_sort.c
void					dynamic_chunk_sort(t_stack *a, t_stack *b,
							int total_size, t_operation **op_list);
// chunk_sort_utils.c
t_node					*find_closest(t_stack *stack, int min, int max,
							t_rotation_params *rot);
void					move_to_top_stack_a(t_stack *a, int direction,
							int moves, t_operation **op_list);
// chunk_utils.c
int						determine_chunk_size(int size, int chunks);
int						determine_chunks_count(int size);
void					determine_chunk_limits(t_stack *a, int chunk_size,
							int *min, int *max);
// operations.c
void					add_operation(t_operation **head, const char *op);
void					free_operations(t_operation *head);
void					print_operations(t_operation *head);
void					optimize_operations(t_operation **head);
// optimization_utils.c
int						try_cancel_operations(t_operation **prev);
int						try_merge_operations(t_operation *curr);
// validation.c
void					check_no_args(int argc, t_program_data *data);
void					check_numeric_args(int argc, char **argv,
							t_program_data *data);
void					check_int_limits_args(int argc, char **argv,
							t_program_data *data);
void					check_duplicates_args(int argc, char **argv,
							t_program_data *data);
// parsing.c
char					**split_in_quotes_args(int *argc, char **argv);
void					free_arguments(char **argv, int argc, int was_split);
void					parse_and_push_args(t_stack *stack, int argc,
							char **argv);
// push_swap.c
void					cleanup(t_program_data *data);
#endif