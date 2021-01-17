#include "minishell.h"
#include "token.h"
#include <stdlib.h>


token_T* init_token(int type, char* value)
{
	token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
	token->type = type;
	token->value = value;

	return token;
}



// Input program

// Current token

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

// Ensure that the current token is TK_CMD.
char **expect_command()
{
	Token   *tmp;
	char    **cmds;
	size_t	size;
	size_t	i;

	if (token->kind != TK_CMD)
		error_at(token->command, "expected a command");
	tmp = token;
	size = 0;
	while (tmp->kind == TK_CMD)
	{
		size++;
		tmp = tmp->next;
	}
	cmds = ft_calloc(size + 1, sizeof(char*));
	i = 0;
	while (token->kind == TK_CMD)
	{
		cmds[i++] = token->command;
		token = token->next;
	}
	cmds[i] = NULL;
	return cmds;
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
