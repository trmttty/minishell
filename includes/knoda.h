/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   knoda.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/16 23:10:41 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KNODA_H
# define KNODA_H

#include "minishell.h"
#include "parser.h"

int		evaluate(t_node *node);

// t_node	*new_node(char **cmd, char *op, t_node *left, t_node *right);
int		sample_exe(char **args);
int		sample_pipe(t_node *node);
int		sample_out_redirect(t_node *node);
int		sample_in_redirect(t_node *node);
int		evaluate(t_node *node);

#endif