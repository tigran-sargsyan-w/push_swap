/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:53:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/05 15:34:22 by tsargsya         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
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

// void optimize_operations(t_operation **head)
// {
//     t_operation dummy;
//     t_operation *prev;
//     t_operation *curr;
//     t_operation *temp;

//     // Create a dummy node that points to the head.
//     dummy.next = *head;
//     prev = &dummy;

//     while (prev->next)
//     {
//         curr = prev->next;
//         if (curr->next)
//         {
//             // --- Merge operations ---
//             // Merge: ra + rb -> rr (in any order)
//             if ((ft_strcmp(curr->op, "ra") == 0 && ft_strcmp(curr->next->op, "rb") == 0) ||
//                 (ft_strcmp(curr->op, "rb") == 0 && ft_strcmp(curr->next->op, "ra") == 0))
//             {
//                 free(curr->op);
//                 curr->op = ft_strdup("rr");
//                 temp = curr->next;
//                 curr->next = temp->next;
//                 free(temp->op);
//                 free(temp);
//                 // Не продвигаем prev, чтобы проверить сформированную пару
//                 continue;
//             }
//             // Merge: rra + rrb -> rrr (in any order)
//             else if ((ft_strcmp(curr->op, "rra") == 0 && ft_strcmp(curr->next->op, "rrb") == 0) ||
//                      (ft_strcmp(curr->op, "rrb") == 0 && ft_strcmp(curr->next->op, "rra") == 0))
//             {
//                 free(curr->op);
//                 curr->op = ft_strdup("rrr");
//                 temp = curr->next;
//                 curr->next = temp->next;
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//             // Merge: sa + sb -> ss (in any order)
//             else if ((ft_strcmp(curr->op, "sa") == 0 && ft_strcmp(curr->next->op, "sb") == 0) ||
//                      (ft_strcmp(curr->op, "sb") == 0 && ft_strcmp(curr->next->op, "sa") == 0))
//             {
//                 free(curr->op);
//                 curr->op = ft_strdup("ss");
//                 temp = curr->next;
//                 curr->next = temp->next;
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
            
//             // --- Cancel operations ---
//             // Cancel: ra + rra (in any order)
//             if ((ft_strcmp(curr->op, "ra") == 0 && ft_strcmp(curr->next->op, "rra") == 0) ||
//                 (ft_strcmp(curr->op, "rra") == 0 && ft_strcmp(curr->next->op, "ra") == 0))
//             {
//                 temp = curr->next;
//                 prev->next = temp->next;
//                 free(curr->op);
//                 free(curr);
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//             // Cancel: rb + rrb (in any order)
//             else if ((ft_strcmp(curr->op, "rb") == 0 && ft_strcmp(curr->next->op, "rrb") == 0) ||
//                      (ft_strcmp(curr->op, "rrb") == 0 && ft_strcmp(curr->next->op, "rb") == 0))
//             {
//                 temp = curr->next;
//                 prev->next = temp->next;
//                 free(curr->op);
//                 free(curr);
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//             // Cancel: double operation sa (sa + sa)
//             else if (ft_strcmp(curr->op, "sa") == 0 && ft_strcmp(curr->next->op, "sa") == 0)
//             {
//                 temp = curr->next;
//                 prev->next = temp->next;
//                 free(curr->op);
//                 free(curr);
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//             // Cancel: double operation sb (sb + sb)
//             else if (ft_strcmp(curr->op, "sb") == 0 && ft_strcmp(curr->next->op, "sb") == 0)
//             {
//                 temp = curr->next;
//                 prev->next = temp->next;
//                 free(curr->op);
//                 free(curr);
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//             // Cancel: double operation ss (ss + ss)
//             else if (ft_strcmp(curr->op, "ss") == 0 && ft_strcmp(curr->next->op, "ss") == 0)
//             {
//                 temp = curr->next;
//                 prev->next = temp->next;
//                 free(curr->op);
//                 free(curr);
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//             // Cancel: pa + pb (in any order, assuming the element returns to its original position)
//             else if ((ft_strcmp(curr->op, "pa") == 0 && ft_strcmp(curr->next->op, "pb") == 0) ||
//                      (ft_strcmp(curr->op, "pb") == 0 && ft_strcmp(curr->next->op, "pa") == 0))
//             {
//                 temp = curr->next;
//                 prev->next = temp->next;
//                 free(curr->op);
//                 free(curr);
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//             // Cancel: rr + rrr (in any order)
//             else if ((ft_strcmp(curr->op, "rr") == 0 && ft_strcmp(curr->next->op, "rrr") == 0) ||
//                      (ft_strcmp(curr->op, "rrr") == 0 && ft_strcmp(curr->next->op, "rr") == 0))
//             {
//                 temp = curr->next;
//                 prev->next = temp->next;
//                 free(curr->op);
//                 free(curr);
//                 free(temp->op);
//                 free(temp);
//                 continue;
//             }
//         }
//         // Если ни одна оптимизация не сработала — двигаемся дальше.
//         prev = curr;
//     }
//     *head = dummy.next;
// }




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
