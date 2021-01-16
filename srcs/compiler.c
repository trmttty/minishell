/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:16:07 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/16 21:17:31 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compiler.h"

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


Node *new_node(NodeKind kind) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;
  return node;
}

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs) {
  Node *node = new_node(kind);
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node *new_cmd(char *cmd) {
  Node *node = new_node(ND_CMD);
  node->cmd = cmd;
  return node;
}

// expr = mul ("+" mul | "-" mul)*
Node *expr() {
  Node *node = mul();

  for (;;) {
    if (consume(';'))
      node = new_binary(ND_SEMI, node, mul());
    else
      return node;
  }
}

// mul = unary ("*" unary | "/" unary)*
Node *mul() {
  Node *node = primary();

  for (;;) {
    if (consume('|'))
      node = new_binary(ND_PIPE, node, primary());
    else
      return node;
  }
}

// unary = ("+" | "-")? unary
//       | primary
// Node *unary() {
//   if (consume('+'))
//     return unary();
//   if (consume('-'))
//     return new_binary(ND_SUB, new_num(0), unary());
//   return primary();
// }

// // primary = "(" expr ")" | num
Node *primary() {
  return new_cmd(expect_command());
}

//
// Code generator
//

void gen(Node *node) {
  if (node->kind == ND_CMD) {
    printf("  CMD %s\n", node->cmd);
    return;
  }

  gen(node->lhs);
  gen(node->rhs);

  switch (node->kind) {
  case ND_SEMI:
    printf("  SEMI\n");
    break;
  case ND_PIPE:
    printf("  PIPE\n");
    break;
  }
}

// int main(int argc, char **argv) {
//   if (argc != 2)
//     return 1;

//   // Tokenize and parse.
//   user_input = argv[1];
//   token = tokenize();
//   Node *node = expr();

//   // Traverse the AST to emit assembly.
//   gen(node);

//   return 0;
// }