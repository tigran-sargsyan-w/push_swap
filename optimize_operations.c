/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:33:44 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/05 18:48:42 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"
#include <stdlib.h>


// // Удаление текущей и следующей операции
// void remove_next_operation(t_operation **prev) {
//     t_operation *curr = (*prev)->next;
//     t_operation *temp = curr->next;

//     (*prev)->next = temp->next;
//     free(curr->op);
//     free(curr);
//     free(temp->op);
//     free(temp);
// }

// // Объединение двух операций в одну
// void merge_operations(t_operation *curr, const char *new_op) {
//     t_operation *temp = curr->next;
//     free(curr->op);
//     curr->op = ft_strdup(new_op);
//     curr->next = temp->next;
//     free(temp->op);
//     free(temp);
// }

// // Проверка и слияние операций
// int try_merge_operations(t_operation *curr) {
//     if ((ft_strcmp(curr->op, "ra") == 0 && ft_strcmp(curr->next->op, "rb") == 0) ||
//         (ft_strcmp(curr->op, "rb") == 0 && ft_strcmp(curr->next->op, "ra") == 0)) {
//         merge_operations(curr, "rr");
//         return 1;
//     }
//     if ((ft_strcmp(curr->op, "rra") == 0 && ft_strcmp(curr->next->op, "rrb") == 0) ||
//         (ft_strcmp(curr->op, "rrb") == 0 && ft_strcmp(curr->next->op, "rra") == 0)) {
//         merge_operations(curr, "rrr");
//         return 1;
//     }
//     if ((ft_strcmp(curr->op, "sa") == 0 && ft_strcmp(curr->next->op, "sb") == 0) ||
//         (ft_strcmp(curr->op, "sb") == 0 && ft_strcmp(curr->next->op, "sa") == 0)) {
//         merge_operations(curr, "ss");
//         return 1;
//     }
//     return 0;
// }

// // Проверка и удаление противоположных операций
// int try_cancel_operations(t_operation **prev) {
//     t_operation *curr = (*prev)->next;
//     if ((ft_strcmp(curr->op, "ra") == 0 && ft_strcmp(curr->next->op, "rra") == 0) ||
//         (ft_strcmp(curr->op, "rra") == 0 && ft_strcmp(curr->next->op, "ra") == 0) ||
//         (ft_strcmp(curr->op, "rb") == 0 && ft_strcmp(curr->next->op, "rrb") == 0) ||
//         (ft_strcmp(curr->op, "rrb") == 0 && ft_strcmp(curr->next->op, "rb") == 0) ||
//         (ft_strcmp(curr->op, "sa") == 0 && ft_strcmp(curr->next->op, "sa") == 0) ||
//         (ft_strcmp(curr->op, "sb") == 0 && ft_strcmp(curr->next->op, "sb") == 0) ||
//         (ft_strcmp(curr->op, "ss") == 0 && ft_strcmp(curr->next->op, "ss") == 0) ||
//         (ft_strcmp(curr->op, "pa") == 0 && ft_strcmp(curr->next->op, "pb") == 0) ||
//         (ft_strcmp(curr->op, "pb") == 0 && ft_strcmp(curr->next->op, "pa") == 0) ||
//         (ft_strcmp(curr->op, "rr") == 0 && ft_strcmp(curr->next->op, "rrr") == 0) ||
//         (ft_strcmp(curr->op, "rrr") == 0 && ft_strcmp(curr->next->op, "rr") == 0)) {
//         remove_next_operation(prev);
//         return 1;
//     }
//     return 0;
// }

// // Основная функция оптимизации
// void optimize_operations(t_operation **head) {
//     t_operation dummy;
//     t_operation *prev = &dummy;

//     dummy.next = *head;
//     while (prev->next && prev->next->next) {
//         if (try_merge_operations(prev->next) || try_cancel_operations(&prev))
//             continue;
//         prev = prev->next;
//     }
//     *head = dummy.next;
// }








// Для слияния используем ту же проверку, что и is_pair_or_reverse
int is_mergeable(const char *op1, const char *op2, const char *a, const char *b)
{
	int first;
	int second;

	first = (ft_strcmp(op1, a) == 0 && ft_strcmp(op2, b) == 0);
    second = (ft_strcmp(op1, b) == 0 && ft_strcmp(op2, a) == 0);
    return (first || second);
}

// Каждая функция ниже возвращает 1, если пара операций должна быть отменена

int is_paired(const char *op1,const char *op2,char *first,char *second)
{
	if (ft_strcmp(op1, first) == 0 && ft_strcmp(op2, second) == 0)
		return (1);
	if (ft_strcmp(op1, second) == 0 && ft_strcmp(op2, first) == 0)
		return (1);
	return (0);
}


int is_ra_rra(const char *op1, const char *op2)
{
	char *first_op;
	char *second_op;
	int first;
	int second;

	first_op = "ra";
	second_op = "rra";
	first = (ft_strcmp(op1, first_op) == 0 && ft_strcmp(op2, second_op) == 0);
    second = (ft_strcmp(op1, second_op) == 0 && ft_strcmp(op2, first_op) == 0);
    return (first || second);
}

int is_rb_rrb(const char *op1, const char *op2)
{
	char *first_op;
	char *second_op;
	int first;
	int second;

	first_op = "rb";
	second_op = "rrb";
	first = (ft_strcmp(op1, first_op) == 0 && ft_strcmp(op2, second_op) == 0);
    second = (ft_strcmp(op1, second_op) == 0 && ft_strcmp(op2, first_op) == 0);
    return (first || second);
}

int is_double_sa(const char *op1, const char *op2) 
{
	int result;
	char *op;
	
	op = "sa";
	result = (ft_strcmp(op1, op) == 0 && ft_strcmp(op2, op) == 0);
    return (result);
}

int is_double_sb(const char *op1, const char *op2)
{
	int result;
	char *op;
	
	op = "sb";
	result = (ft_strcmp(op1, op) == 0 && ft_strcmp(op2, op) == 0);
    return (result);
}

int is_double_ss(const char *op1, const char *op2)
{
	int result;
	char *op;
	
	op = "ss";
	result = (ft_strcmp(op1, op) == 0 && ft_strcmp(op2, op) == 0);
    return (result);
}

int is_pa_pb(const char *op1, const char *op2)
{
	char *first_op;
	char *second_op;
	int first;
	int second;

	first_op = "pa";
	second_op = "pb";
	first = (ft_strcmp(op1, first_op) == 0 && ft_strcmp(op2, second_op) == 0);
    second = (ft_strcmp(op1, second_op) == 0 && ft_strcmp(op2, first_op) == 0);
    return (first || second);
}

int is_rr_rrr(const char *op1, const char *op2)
{
	char *first_op;
	char *second_op;
	int first;
	int second;

	first_op = "rr";
	second_op = "rrr";
	first = (ft_strcmp(op1, first_op) == 0 && ft_strcmp(op2, second_op) == 0);
    second = (ft_strcmp(op1, second_op) == 0 && ft_strcmp(op2, first_op) == 0);
    return (first || second);
}

int is_cancelable(const char *op1,const char *op2)
{
	if(is_paired(op1, op2,"ra","rra"))
		return (1);
    // if (is_ra_rra(op1, op2))
	// 	return 1;
	if(is_paired(op1, op2,"rb","rrb"))
		return (1);
    // if (is_rb_rrb(op1, op2))
	// 	return 1;
    if (is_double_sa(op1, op2))
		return 1;
    if (is_double_sb(op1, op2))
		return 1;
    if (is_double_ss(op1, op2))
		return 1;
	if(is_paired(op1, op2,"pa","pb"))
		return (1);
    // if (is_pa_pb(op1, op2))
	// 	return 1;
	if(is_paired(op1, op2,"rr","rrr"))
		return (1);
    // if (is_rr_rrr(op1, op2))
	// 	return 1;
    return 0;
}

// Объединённая функция, проверяющая все пары для отмены
int is_cancelable_pair(const char *op1, const char *op2) {
    if (is_ra_rra(op1, op2))    return 1;
    if (is_rb_rrb(op1, op2))    return 1;
    if (is_double_sa(op1, op2)) return 1;
    if (is_double_sb(op1, op2)) return 1;
    if (is_double_ss(op1, op2)) return 1;
    if (is_pa_pb(op1, op2))     return 1;
    if (is_rr_rrr(op1, op2))    return 1;
    return 0;
}

/*
 * Функция удаления пары операций.
 * При отмене пары операций удаляются и текущая, и следующая.
 */
void remove_next_operation(t_operation **prev) {
    t_operation *curr = (*prev)->next;
    t_operation *temp = curr->next;

    (*prev)->next = temp->next;
    free(curr->op);
    free(curr);
    free(temp->op);
    free(temp);
}

/*
 * Функция, которая пытается отменить операции.
 * Если отмена прошла успешно, возвращает 1, иначе 0.
 */
int try_cancel_operations(t_operation **prev) {
    t_operation *curr = (*prev)->next;

    if (!curr || !curr->next)
        return 0;

    // if (is_cancelable_pair(curr->op, curr->next->op)) {
    if (is_cancelable(curr->op, curr->next->op)) {
        remove_next_operation(prev);
        return 1;
    }
    return 0;
}

/*
 * Функции для слияния операций (merge)
 */

// Объединяет две операции в одну, заменяя текущую операцию на new_op
void merge_operations(t_operation *curr, const char *new_op)
{
    t_operation *temp = curr->next;
    free(curr->op);
    curr->op = ft_strdup(new_op);
    curr->next = temp->next;
    free(temp->op);
    free(temp);
}



// Проверяем варианты слияния: "ra"+"rb" -> "rr", "rra"+"rrb" -> "rrr", "sa"+"sb" -> "ss"
int try_merge_operations(t_operation *curr) {
    if (is_mergeable(curr->op, curr->next->op, "ra", "rb")) {
        merge_operations(curr, "rr");
        return 1;
    }
    if (is_mergeable(curr->op, curr->next->op, "rra", "rrb")) {
        merge_operations(curr, "rrr");
        return 1;
    }
    if (is_mergeable(curr->op, curr->next->op, "sa", "sb")) {
        merge_operations(curr, "ss");
        return 1;
    }
    return 0;
}

/*
 * Основная функция оптимизации списка операций.
 * Она проходит по списку и пытается выполнить слияние или отмену пары операций.
 */
void optimize_operations(t_operation **head) {
    t_operation dummy;
    t_operation *prev = &dummy;

    dummy.next = *head;

    // Проходим по списку, пока есть хотя бы две операции подряд
    while (prev->next && prev->next->next) {
        // Если удалось объединить или отменить пару операций, остаёмся на текущем месте,
        // чтобы проверить, не образовалась ли новая оптимизируемая пара.
        if (try_merge_operations(prev->next) || try_cancel_operations(&prev))
            continue;
        prev = prev->next;
    }

    *head = dummy.next;
}