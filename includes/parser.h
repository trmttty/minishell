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
typedef enum {
	ND_SEMI,        // ;
	ND_PIPE,        // |
	ND_GREAT,       // >
	ND_GREATGREAT,  // >>
	ND_LESS,        // <
	ND_CMD,         // command
} NodeKind;

typedef struct		s_node
{
	NodeKind		kind; // t_node kind
	//関数名、
	char			**command;
	//"|", ">", ";",etc.
	char			*operation;
	struct s_node	*lnode;
	struct s_node	*rnode;
}					t_node;


t_node *new_node(NodeKind kind);

t_node *new_binary(NodeKind kind, t_node *lhs, t_node *rhs);

t_node *new_cmd(char **cmd);

t_node *command_line();

t_node *job();

t_node *command();

t_node *simple_command();

//
// Code generator
//
void gen(t_node *node);

#endif
