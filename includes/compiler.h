#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Tokenizer
//

typedef enum {
  TK_RESERVED, // Keywords or punctuators
  TK_CMD,      // Integer literals
  TK_EOF,      // End-of-file markers
} TokenKind;

// Token type
typedef struct Token Token;
struct Token {
  TokenKind kind; // Token kind
  Token     *next;    // Next token
  char      *command;        // If kind is TK_NUM, its value
  char      *operator;      // Token string
};

// Input program
char *user_input;

// Current token
Token *token;

// // Reports an error and exit.
// void error(char *fmt, ...) {
//   va_list ap;
//   va_start(ap, fmt);
//   vfprintf(stderr, fmt, ap);
//   fprintf(stderr, "\n");
//   exit(1);
// }

// Reports an error location and exit.
void error_at(char *loc, char *fmt, ...);

// Consumes the current token if it matches `op`.
bool consume(char op);

// Ensure that the current token is `op`.
void expect(char op);

// Ensure that the current token is TK_NUM.
char *expect_command();

bool at_eof();

// Create a new token and add it as the next token of `cur`.
Token *new_token(TokenKind kind, Token *cur, char *op);

//
// Parser
//

typedef enum {
  ND_SEMI, // ;
  ND_PIPE, // |
  ND_CMD, // Integer
} NodeKind;

// AST node type
typedef struct Node Node;
struct Node {
  NodeKind kind; // Node kind
  Node *lhs;     // Left-hand side
  Node *rhs;     // Right-hand side
  char  *cmd;       // Used if kind == ND_NUM
};

Node *new_node(NodeKind kind);

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);

Node *new_cmd(char *cmd);

// expr = mul ("+" mul | "-" mul)*
Node *expr();

// mul = unary ("*" unary | "/" unary)*
Node *mul();

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
Node *primary();

//
// Code generator
//

void gen(Node *node);