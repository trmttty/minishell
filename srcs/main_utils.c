/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:38:26 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/12 15:28:50 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "signal.h"
#include "evaluate.h"

int		ft_iswspace_str(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

int		set_exit_status(int status)
{
	if (status == 0)
		return (set_question("?", "0"));
	else if (status == 126)
		return (set_question("?", "126"));
	else if (status == 127)
		return (set_question("?", "127"));
	else if (status == INT_STATUS)
		return (set_question("?", "130"));
	else if (status == QUIT_STATUS)
		return (set_question("?", "131"));
	else
		return (set_question("?", "1"));
}
