/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:16:07 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 02:17:16 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "token.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	if ((node = ft_calloc(1, sizeof(t_node))) == NULL)
		ft_perror("minishell");
	node->kind = kind;
	return (node);
}

t_node	*new_binary(t_node_kind kind, t_node *lhs, t_node *rhs)
{
	t_node	*node;

	node = new_node(kind);
	node->lnode = lhs;
	node->rnode = rhs;
	return (node);
}

t_node	*new_cmd(char **cmd)
{
	t_node	*node;

	node = new_node(ND_CMD);
	node->commands = cmd;
	return (node);
}

void	free_node(t_node *node)
{
	if (node->lnode)
		free_node(node->lnode);
	if (node->rnode)
		free_node(node->rnode);
	if (node->commands)
		ft_tabfree(node->commands);
	if (node)
		free(node);
}
