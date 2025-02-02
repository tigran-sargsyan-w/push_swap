/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:53:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/02 19:09:44 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_printf.h"
#include "libft/libft.h"
#include "push_swap.h"
#include <stdlib.h>

void	add_operation(t_operation **op_list, const char *op)
{
	t_operation	*new_node;
	t_operation	*tmp;

	new_node = malloc(sizeof(t_operation));
	if (!new_node)
		exit(1);
	new_node->op = ft_strdup(op);
	if (!new_node->op)
	{
		ft_printf("Ошибка выделения памяти для строки операции");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	if (*op_list == NULL)
	{
		*op_list = new_node;
	}
	else
	{
		tmp = *op_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}

void	optimize_operations(t_operation **head)
{
	t_operation	*current;
	t_operation	*temp;

	current = *head;
	while (current && current->next)
	{
		if ((ft_strcmp(current->op, "ra") == 0 && ft_strcmp(current->next->op,
					"rb") == 0) ||
			(ft_strcmp(current->op, "rb") == 0 && ft_strcmp(current->next->op,
						"ra") == 0))
		{
			free(current->op);
			current->op = ft_strdup("rr");
			temp = current->next;
			current->next = temp->next;
			free(temp->op);
			free(temp);
		}
		else if ((ft_strcmp(current->op, "rra") == 0
					&& ft_strcmp(current->next->op, "rrb") == 0) ||
					(ft_strcmp(current->op, "rrb") == 0
							&& ft_strcmp(current->next->op, "rra") == 0))
		{
			free(current->op);
			current->op = ft_strdup("rrr");
			temp = current->next;
			current->next = temp->next;
			free(temp->op);
			free(temp);
		}
		else
		{
			current = current->next;
		}
	}
}

void	free_operations(t_operation *head)
{
	t_operation	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->op);
		free(tmp);
	}
}

void	print_operations(t_operation *head)
{
	while (head)
	{
		ft_printf("%s\n", head->op);
		head = head->next;
	}
}
