/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/06 12:37:43 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"

t_lexer		*new_lexer(char *contents)
{
	t_lexer	*lexer;

	if ((lexer = ft_calloc(1, sizeof(t_lexer))) == NULL)
		ft_perror("minishell");
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	lexer->nc = contents[lexer->i + 1];
	if (ft_isquote(lexer->c))
		lexer->quote = lexer->c;
	return (lexer);
}

void		lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->pc = lexer->contents[lexer->i];
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
		lexer->nc = lexer->contents[lexer->i + 1];
	}
	in_bracket(lexer);
	// in_bracket(lexer);
}

void		lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
	{
		lexer_advance(lexer);
	}
}

int			is_escaped(char *str, int pos)
{
	int	n;

	n = 0;
	while (pos >= 0 && str[pos] == '\\')
	{
		n++;
		pos--;
	}
	return (n % 2);
}

// int			in_bracket(char *str, int pos)
// {
// 	int	dquote;
// 	int	squote;
// 	int	i;

// 	dquote = 0;
// 	squote = 0;
// 	i = 0;
// 	while (i <= pos)
// 	{
// 		if (str[i] == '"' && (i == 0 || !is_escaped(str, i - 1))
// 			&& squote % 2 == 0)
// 			dquote++;
// 		else if (str[i] == '\''
// 				&& (i == 0 || squote % 2 != 0 || !is_escaped(str, i - 1))
// 				&& dquote % 2 == 0)
// 			squote++;
// 		i++;
// 	}
// 	if (dquote % 2 != 0 || squote % 2 != 0)
// 		return (1);
// 	return (0);
// }

int			ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}

int			in_bracket(t_lexer *lexer)
{
	if (lexer->quote == '\0' && ft_isquote(lexer->c)) 
	{
		lexer->quote = lexer->c;
		return (1);
	}
	if (ft_isquote(lexer->quote) && lexer->quote == lexer->c)
	{
		lexer->quote = '\0';
		return (0);
	}
	return (ft_isquote(lexer->quote));
}
