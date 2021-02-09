/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:55:18 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/07 14:14:36 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATE_H
# define EVALUATE_H
# include "minishell.h"
# include "parser.h"

int		ft_pipe(t_node *node, int *flag);
int		ft_redirect_out(t_node *node, int *flag);
int		ft_redirect_outout(t_node *node, int *flag);
int		ft_redirect_in(t_node *node, int *flag);
int		evaluate(t_node *node, int *flag);

#endif
