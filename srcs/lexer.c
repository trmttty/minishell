/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:26:55 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/18 12:26:59 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


t_lexer* init_lexer(char* contents)
{
    t_lexer* lexer;
    
    lexer = calloc(1, sizeof(t_lexer));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void lexer_advance(t_lexer* lexer)
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

// whitespace?????
void lexer_skip_whitespace(t_lexer* lexer)
{
    while (lexer->c == ' ' || lexer->c == '\n')
    {
        lexer_advance(lexer);
    }
}

t_token* lexer_get_next_token(t_lexer* lexer)
{
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        if (lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);

        if (isalnum(lexer->c) || lexer->c == '-')
            return (lexer_collect_id(lexer));

        if (lexer->c == '"')
            return (lexer_collect_string(lexer));

        if (ft_strchr(";()<>|$", lexer->c))
            return (lexer_advance_with_token(lexer, init_token(TK_RESERVED, lexer_get_current_char_as_string(lexer))));
    }
    return (NULL);
}

t_token* lexer_collect_string(t_lexer* lexer)
{
    char    *value;
    char    *s;
    size_t  size;

    lexer_advance(lexer);

    value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '"')
    {
        s = lexer_get_current_char_as_string(lexer);
        size = ft_strlen(value) + ft_strlen(s) + 1;
        value = realloc(value, size * sizeof(char));
        ft_strlcat(value, s, size);

        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(TK_CMD, value);
}

t_token* lexer_collect_id(t_lexer* lexer)
{
    char*   value;
    char*   s;
    size_t  size;
    
    value = ft_calloc(1, sizeof(char));
    value[0] = '\0';
    while (isalnum(lexer->c) || lexer->c == '-')
    {
        s = lexer_get_current_char_as_string(lexer);
        size = ft_strlen(value) + ft_strlen(s) + 1;
        value = realloc(value, size * sizeof(char));
        ft_strlcat(value, s, size);

        lexer_advance(lexer);
    }

    return init_token(TK_CMD, value);
}

t_token* lexer_advance_with_token(t_lexer* lexer, t_token* token)
{
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(t_lexer* lexer)
{
    char* str = ft_calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}
