/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:12:09 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/01/31 22:12:25 by kazumanoda       ###   ########.fr       */
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
