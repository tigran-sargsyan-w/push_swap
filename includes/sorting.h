/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:08:37 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/19 19:37:18 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTING_H
# define SORTING_H

# include "operations.h"
# include "stack.h"

typedef struct s_rotation_params
{
	int	moves;
	int	direction;
}		t_rotation_params;

void	assign_sorted_indices(t_stack *a);
int		is_sorted_and_b_empty(t_stack *a, t_stack *b);
void	sort_three(t_stack *stack, t_operation **op_list);
void	sort_four(t_stack *a, t_stack *b, t_operation **op_list);
void	sort_five(t_stack *a, t_stack *b, t_operation **op_list);
void	dynamic_chunk_sort(t_stack *a, t_stack *b, int total_size,
			t_operation **op_list);
t_node	*find_closest(t_stack *stack, int min, int max, t_rotation_params *rot);
void	move_to_top_stack_a(t_stack *a, int direction, int moves,
			t_operation **op_list);
int		determine_chunk_size(int size, int chunks);
int		determine_chunks_count(int size);
void	determine_chunk_limits(t_stack *a, int chunk_size, int *min, int *max);

#endif
