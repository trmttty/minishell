/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:27:13 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/25 21:15:48 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include "lexer.h"
#include <stdlib.h>


t_token* init_token(t_token_kind type, char* value)
{
	t_token* token = calloc(1, sizeof(t_token));
	token->kind = type;
	token->value = value;
	return (token);
}



// Input program

// Current token

// Reports an error location and exit.
void error_at(char *loc, char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	// int pos = loc - user_input;
	// fprintf(stderr, "%s\n", user_input);
	// fprintf(stderr, "%*s", pos, ""); // print pos spaces.
	fprintf(stderr, "^ ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

// Consumes the current token if it matches `op`.
bool consume(char *op) {
	if (g_token->kind != TK_RESERVED || ft_strcmp(g_token->value, op))
		return false;
	g_token = g_token->next;
	return true;
}

// Ensure that the current token is `op`.
void expect(char op) {
	if (g_token->kind != TK_RESERVED || g_token->value[0] != op)
		error_at(g_token->value, "expected '%c'", op);
	g_token = g_token->next;
}

// Ensure that the current token is TK_CMD.
char **expect_command()
{
	t_token	*tmp;
	char    **cmds;
	size_t	size;
	size_t	i;

	if (g_token->kind != TK_CMD)
		;
		// error_at(token->command, "expected a command");
	tmp = g_token;
	size = 0;
	while (tmp->kind == TK_CMD)
	{
		size++;
		tmp = tmp->next;
	}
	cmds = ft_calloc(size + 1, sizeof(char*));
	i = 0;
	while (g_token->kind == TK_CMD)
	{
		cmds[i++] = g_token->value;
		g_token = g_token->next;
	}
	cmds[i] = NULL;
	return cmds;
}

bool at_eof() {
	return g_token->kind == TK_EOF;
}

// Create a new token and add it as the next token of `cur`.
t_token *new_token(t_token_kind kind, t_token *cur, char *value) {
	t_token *token = calloc(1, sizeof(t_token));
	token->kind = kind;
	token->value = value;
	cur->next = token;
	return (token);
}

t_token		*validate_token(char *job)
{
	t_lexer		*lexer;
	t_token		*token;
	t_token		token_head;
	t_token		*cur;

	lexer = init_lexer(job);
	token_head.next = NULL;
	cur = &token_head;
	while ((token = lexer_get_next_token(lexer)) != NULL)
	{
		// // printf("token:	[%s]\n", token->value);
		// size_t len1 = ft_strlen(token->value);
		// token->value = replace_env(token->value);
		// // printf("env:	[%s]\n", token->value);
		// token->value = remove_quote(token->value);
		// size_t len2 = ft_strlen(token->value);
		// // printf("quote:	[%s]\n", token->value);
		// if (len1 && !len2)
		// {
		// 	// cur->next = token;
		// 	continue;
		// }
		cur = new_token(token->kind, cur, token->value);
	}
	new_token(TK_EOF, cur, NULL);
	return(token_head.next);
}

t_token		*tokenize(char *job)
{
	t_lexer		*lexer;
	t_token		*token;
	t_token		token_head;
	t_token		*cur;

	lexer = init_lexer(job);
	token_head.next = NULL;
	cur = &token_head;
	while ((token = lexer_get_next_token(lexer)) != NULL)
	{
		// printf("token:	[%s]\n", token->value);
		size_t len1 = ft_strlen(token->value);
		token->value = replace_env(token->value);
		// printf("env:	[%s]\n", token->value);
		token->value = remove_quote(token->value);
		size_t len2 = ft_strlen(token->value);
		// printf("quote:	[%s]\n", token->value);
		if (len1 && !len2)
		{
			// cur->next = token;
			continue;
		}
		cur = new_token(token->kind, cur, token->value);
	}
	new_token(TK_EOF, cur, NULL);
	return(token_head.next);
}