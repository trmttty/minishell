/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knoda.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/18 22:00:01 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KNODA_H
# define KNODA_H

#include "minishell.h"
#include "parser.h"

int		evaluate(t_node *node, int *flag);

// t_node	*new_node(char **cmd, char *op, t_node *left, t_node *right);
// int		sample_exe(char **args);
// int		sample_pipe(t_node *node);
// int		sample_out_redirect(t_node *node);
// int		sample_in_redirect(t_node *node);
// int		evaluate(t_node *node);

#endif
