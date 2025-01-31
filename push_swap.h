/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:27:11 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/31 21:01:50 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
	t_node			*bottom;
	int				size;
}					t_stack;

typedef struct s_rotation
{
	int				count;
	int				direction;
}					t_rotation;

// Stack functions
t_stack				*stack_init(void);
void				stack_push(t_stack *stack, int value);
int					stack_pop(t_stack *stack);
int					stack_peek(t_stack *stack);
int					stack_is_empty(t_stack *stack);
void				stack_clear(t_stack *stack);

// Operations push_swap
void				sa(t_stack *a);
void				sb(t_stack *b);
void				ss(t_stack *a, t_stack *b);
void				pa(t_stack *a, t_stack *b);
void				pb(t_stack *a, t_stack *b);
void				ra(t_stack *a);
void				rb(t_stack *b);
void				rr(t_stack *a, t_stack *b);
void				rra(t_stack *a);
void				rrb(t_stack *b);
void				rrr(t_stack *a, t_stack *b);

// Utils
void				print_stack(t_stack *stack);
void				print_stack_index(t_stack *stack);

// Sorting
void				assign_sorted_indices(t_stack *a);
void				radix_sort(t_stack *a, t_stack *b, int size);
void				chunk_sort(t_stack *a, t_stack *b, int size, int chunks);
int					determine_chunks(int size);

#endif