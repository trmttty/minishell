#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT
{
		enum
		{
				TOKEN_ID,
				TOKEN_STRING,
				TOKEN_SEMI,
				TOKEN_LPAREN,
				TOKEN_RPAREN,
				TOKEN_LREDIRECT,
				TOKEN_RREDIRECT,
				TOKEN_PIPE,
				TOKEN_OPTION,
				TOKEN_ENV,
				TOKEN_EOF
		} type;

		char* value;
} token_T;

token_T* init_token(int type, char* value);




#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Tokenizer
//

typedef enum		u_token_kind{
	TK_RESERVED, // Keywords or punctuators
	TK_CMD,      // Integer literals
	TK_EOF,      // End-of-file markers
}					t_token_kind;

// Token type
typedef struct		s_token
{
	t_token_kind	kind;
	char			*command;	// If kind is TK_NUM, its value
	char			*operator;	// Token string
	struct s_token	*next;		// Next token
}					t_token;


// Input program
char *user_input;

// Current token
t_token	*token;

void error(char *fmt, ...);

// Reports an error location and exit.
void error_at(char *loc, char *fmt, ...);

// Consumes the current token if it matches `op`.
bool consume(char op);

// Ensure that the current token is `op`.
void expect(char op);

// Ensure that the current token is TK_NUM.
char **expect_command();

bool at_eof();

// Create a new token and add it as the next token of `cur`.
t_token *new_token(t_token_kind kind, t_token *cur, char *op);

#endif
