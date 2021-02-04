/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:16:07 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/04 09:07:09 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "token.h"

/*** Shell Grammer for recursive descent parser ***/
/**
	<command line>	::= 	<job> ';' <command line>
						|	<job> ';'
						|	<job>
	<job>			::=		<command> '|' <job>
						|	<command>
	<command>		::=		<simple command> '<'  <filename>
						|	<simple command> '>'  <filename>
						|	<simple command> '>>' <filename>
						|	<simple command>
	<simple command>::=		<pathname> <token list>
	<token list>	::=		<token> <token list>
						|	(EMPTY)
**/

t_node *new_node(t_node_kind kind) {
	t_node	*node;
	
	if ((node = ft_calloc(1, sizeof(t_node))) == NULL)
		ft_perror("minishell");
	node->kind = kind;
	return (node);
}

t_node *new_binary(t_node_kind kind, t_node *lhs, t_node *rhs) {
	t_node	*node;
	
	node = new_node(kind);
	node->lnode = lhs;
	node->rnode = rhs;
	return (node);
}

t_node *new_cmd(char **cmd) {
	t_node	*node;

	node = new_node(ND_CMD);
	node->commands = cmd;
	return (node);
}

t_node *command_line() {
	t_node	*node;
	
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

t_node *job() {
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

t_node *command() {
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

t_node *simple_command() {
	return (new_cmd(expect_command()));
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

// Code generator

void gen(t_node *node) {
	// printf("%s %d\n", node->operation, node->kind);
	if (node->kind == ND_CMD) {
		while (*node->commands)
		{
			printf("  CMD %s\n", node->commands[0]);
			(node->commands)++;
		}
		return;
	}

	gen(node->lnode);
	gen(node->rnode);

	switch (node->kind) {
	case ND_SEMI:
		printf("  SEMI\n");
		break;
	case ND_PIPE:
		printf("  PIPE\n");
		break;
	case ND_GREAT:
		printf("  GREAT\n");
		break;
	case ND_GREATGREAT:
		printf("  GREATGREAT\n");
		break;
	case ND_LESS:
		printf("  LESS\n");
		break;
	}
}
