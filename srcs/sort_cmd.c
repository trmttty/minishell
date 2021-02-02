/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:12:09 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/01/31 23:25:35 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sort_cmd.h"

char	*sort_cmd(char *str)
{
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	while (str[i])
	{
		while (ft_strchr(";|", str[i]))
			argc = ++i;
		if ((i = skip_quotation(str, i)) == -1)
			break ;
		if (ft_strchr("<>", str[i]))
			i = skip_redirection(str, i);
		else
			str = move_cmd(str, &i, &argc);
	}
	return (str);
}
