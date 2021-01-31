/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:12:09 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/01/31 20:41:36 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define CMD 0
#define CUT 1
#define LHS 2
#define RHS 3

int		ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
			|| c == ' ');
}

int		cmd_len(char *str, int i)
{
	int		len;

	len = 0;
	while (ft_isspace(str[i + len]))
		len++;
	while (str[i + len] && !ft_strchr("<> ;|", str[i + len]))
		len++;
	return (len);
}

int		skip_quotation(char *str, int i)
{
	if (ft_strchr("\'", str[i]))
	{
		i++;
		while (str[i] && !ft_strchr("\'", str[i]))
			i++;
		if (str[i])
			i++;
		else
			return (-1);
	}
	if (ft_strchr("\"", str[i]))
	{
		i++;
		while (str[i] && !ft_strchr("\"", str[i]))
			i++;
		if (str[i])
			i++;
		else
			return (-1);
	}
	return (i);
}

int		skip_redirection(char *str, int i)
{
	i++;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_strchr("<> ;|", str[i]))
	{
		if (ft_strchr("\"\'", str[i]))
			return (i);
		else
			i++;
	}
	return (i);
}

char	*move_cmd(char *str, int *i, int *argc)
{
	int		len;
	char	**l;

	if (!(l = (char **)ft_calloc(5, sizeof(char *))))
		return (str);
	len = cmd_len(str, *i);
	l[CMD] = ft_substr(str, *i, len);
	str[*i] = 0;
	l[CUT] = ft_strjoin(str, &str[*i + len]);
	free(str);
	if (*argc == 0)
		str = ft_strjoin(l[CMD], l[CUT]);
	else
	{
		l[RHS] = ft_substr(l[CUT], *argc, ft_strlen(l[CUT]) - *argc);
		l[CUT][*argc] = 0;
		l[LHS] = ft_strjoin(l[CUT], l[CMD]);
		str = ft_strjoin(l[LHS], l[RHS]);
	}
	*argc += len;
	*i += len;
	ft_tabfree(l);
	return (str);
}

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
