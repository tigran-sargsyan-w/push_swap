/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:09:31 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 17:10:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZATION_H
# define OPTIMIZATION_H

# include "operations.h"

void	add_operation(t_operation **head, const char *op);
void	free_operations(t_operation *head);
void	print_operations(t_operation *head);
void	optimize_operations(t_operation **head);
int		try_cancel_operations(t_operation **prev);
int		try_merge_operations(t_operation *curr);

#endif
