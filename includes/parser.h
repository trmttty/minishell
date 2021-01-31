/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:09:19 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/31 23:12:25 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H 
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Parser
//
typedef enum		u_node_kind
{
	ND_SEMI,        // ;
	ND_PIPE,        // |
	ND_GREAT,       // >
	ND_GREATGREAT,  // >>
	ND_LESS,        // <
	ND_CMD,         // command
}					t_node_kind;

typedef struct		s_node
{
	t_node_kind		kind;
	char			**commands;
	char			*operation; //"|", ">", ";",etc.
	struct s_node	*lnode;
	struct s_node	*rnode;
}					t_node;

t_node *new_node(t_node_kind kind);

t_node *new_binary(t_node_kind kind, t_node *lhs, t_node *rhs);

t_node *new_cmd(char **cmd);

t_node *command_line();

t_node *job();

t_node *command();

t_node *simple_command();

//
// Code generator
//
void	gen(t_node *node);
void	free_node(t_node *node);

#endif
