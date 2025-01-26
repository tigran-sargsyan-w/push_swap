/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:13:16 by tsargsya          #+#    #+#             */
/*   Updated: 2025/01/26 16:47:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "push_swap.h"

// pa: pop from B and push into A
void	pa(t_stack *a, t_stack *b)
{
	int	value;

	if (!b || stack_is_empty(b))
		return ;
	value = stack_pop(b);
	stack_push(a, value);
	ft_printf("pa\n");
}
// pb: pop from A and push into B
void	pb(t_stack *a, t_stack *b)
{
	int value;

	if (!a || stack_is_empty(a))
		return ;
	value = stack_pop(a);
	stack_push(b, value);
	ft_printf("pb\n");
}