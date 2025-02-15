/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:08:53 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/15 17:10:47 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "parsing.h"
# include "stack.h"

void	check_no_args(int argc, t_program_data *data);
void	check_numeric_args(int argc, char **argv, t_program_data *data);
void	check_int_limits_args(int argc, char **argv, t_program_data *data);
void	check_duplicates_args(int argc, char **argv, t_program_data *data);

#endif
