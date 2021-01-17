/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:16:07 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/17 21:51:07 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// Input program

// Current token

// // Reports an error and exit.
// void error(char *fmt, ...) {
//   va_list ap;
//   va_start(ap, fmt);
//   vfprintf(stderr, fmt, ap);
//   fprintf(stderr, "\n");
//   exit(1);
// }

// Reports an error location and exit.
void error_at(char *loc, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, ""); // print pos spaces.
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// Consumes the current token if it matches `op`.
bool consume(char op) {
  if (token->kind != TK_RESERVED || token->operator[0] != op)
    return false;
  token = token->next;
  return true;
}

// Ensure that the current token is `op`.
void expect(char op) {
  if (token->kind != TK_RESERVED || token->operator[0] != op)
    error_at(token->operator, "expected '%c'", op);
  token = token->next;
}

// Ensure that the current token is TK_NUM.
char *expect_command() {
  if (token->kind != TK_CMD)
    error_at(token->command, "expected a command");
  char* cmd = token->command;
  token = token->next;
  return cmd;
}

bool at_eof() {
  return token->kind == TK_EOF;
}

// Create a new token and add it as the next token of `cur`.
Token *new_token(TokenKind kind, Token *cur, char *op) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->operator = op;
  cur->next = tok;
  return tok;
}

// Tokenize `user_input` and returns new tokens.
Token *tokenize() {
  char *p = user_input;
  Token head; head.next = NULL;
  Token *cur = &head;

  while (*p) {
    // Skip whitespace characters.
    if (isspace(*p)) {
      p++;
      continue;
    }

    // Punctuator
    if (strchr("|<>;", *p)) {
      cur = new_token(TK_RESERVED, cur, p++);
      continue;
    }

    // Command
    cur = new_token(TK_CMD, cur, p);
    
    while (*p && !strchr("|<>;", *p))
      p++;
  }

  new_token(TK_EOF, cur, p);
  return head.next;
}

//
// Parser
//


t_node *new_node(NodeKind kind) {
  t_node *node = calloc(1, sizeof(t_node));
  node->kind = kind;
  return node;
}

t_node *new_binary(NodeKind kind, t_node *lhs, t_node *rhs) {
  t_node *node = new_node(kind);

  node->lnode = lhs;
  node->rnode = rhs;
  return node;
}

t_node *new_cmd(char **cmd) {
  t_node *node = new_node(ND_CMD);
  node->command = cmd;
  return node;
}

// expr = mul ("+" mul | "-" mul)*
t_node *command_line() {
  t_node *node = job();

  for (;;) {
    if (consume(';'))
    {
      node = new_binary(ND_SEMI, node, job());
      node->operation = ";";
    }
    else
      return node;
  }
}

// mul = unary ("*" unary | "/" unary)*
t_node *job() {
  t_node *node = command();

  for (;;) {
    if (consume('|'))
    {
        node = new_binary(ND_PIPE, node, command());
        node->operation = "|";
    }
    else
      return node;
  }
}

// unary = ("+" | "-")? unary
//       | primary
// t_node *unary() {
//   if (consume('+'))
//     return unary();
//   if (consume('-'))
//     return new_binary(ND_SUB, new_num(0), unary());
//   return primary();
// }
t_node *command() {
  t_node *node = simple_command();

  for (;;) {
    if (consume('>'))
    {
        node = new_binary(ND_GREAT, node, simple_command());
        node->operation = ">";
    }
    else if (consume('<'))
    {
        node = new_binary(ND_LESS, node, simple_command());
        node->operation = "<";
    }
    else
      return node;
  }
}

// // primary = "(" expr ")" | num
t_node *simple_command() {
  return new_cmd(ft_split(expect_command(), ' '));
}

//
// Code generator
//

void gen(t_node *node) {
  if (node->kind == ND_CMD) {
    printf("  CMD %s\n", node->command[0]);
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
  case ND_LESS:
    printf("  LESS\n");
    break;
  }
}

// int main(int argc, char **argv) {
//   if (argc != 2)
//     return 1;

//   // Tokenize and parse.
//   user_input = argv[1];
//   token = tokenize();
//   t_node *node = expr();

//   // Traverse the AST to emit assembly.
//   gen(node);

//   return 0;
// }