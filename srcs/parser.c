/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:16:07 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/07 00:00:46 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "token.h"

t_node	*command_line(void)
{
	t_node	*node;

	sort_token();
	node = job();
	while (1)
	{
		if (consume(";"))
		{
			node = new_binary(ND_SEMI, node, job());
			node->operation = ";";
		}
		else
			return (node);
	}
}

t_node	*job(void)
{
	t_node	*node;

	node = command();
	while (1)
	{
		if (consume("|"))
		{
			node = new_binary(ND_PIPE, node, command());
			node->operation = "|";
		}
		else
			return (node);
	}
}

t_node	*command(void)
{
	t_node *node;

	node = simple_command();
	while (1)
	{
		if (consume(">>"))
		{
			node = new_binary(ND_GREATGREAT, node, simple_command());
			node->operation = ">>";
		}
		else if (consume(">"))
		{
			node = new_binary(ND_GREAT, node, simple_command());
			node->operation = ">";
		}
		else if (consume("<"))
		{
			node = new_binary(ND_LESS, node, simple_command());
			node->operation = "<";
		}
		else
			return (node);
	}
}

t_node	*simple_command(void)
{
	return (new_cmd(expect_command()));
}
