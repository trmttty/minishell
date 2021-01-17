#ifndef COMPILER_H
# define COMPILER_H

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
  ND_SEMI, // ;
  ND_PIPE, // |
  ND_GREAT,// >
  ND_LESS, // <
  ND_CMD, // Integer
} NodeKind;

// // AST node type
// typedef struct t_node Node;
// struct t_node {
//   NodeKind kind; // t_node kind
//   t_node *lhs;     // Left-hand side
//   t_node *rhs;     // Right-hand side
//   char  *cmd;       // Used if kind == ND_NUM
// };

typedef struct		s_node
{
    NodeKind kind; // t_node kind
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

// expr = mul ("+" mul | "-" mul)*
t_node *command_line();

// mul = unary ("*" unary | "/" unary)*
t_node *job();

// unary = ("+" | "-")? unary
//       | primary
// t_node *unary() {
//   if (consume('+'))
//     return unary();
//   if (consume('-'))
//     return new_binary(ND_SUB, new_num(0), unary());
//   return primary();
// }
t_node *command();

// // primary = "(" expr ")" | num
t_node *simple_command();

//
// Code generator
//

void gen(t_node *node);

#endif
