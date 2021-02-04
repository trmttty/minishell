/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 22:06:33 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/04 19:15:28 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sort_cmd.h"

int		ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
			|| c == ' ');
}

int		quotation_len(char *str, int i)
{
	int		tmp;

	tmp = i;
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
	return (i - tmp);
}

int		cmd_len(char *str, int *i)
{
	int		len;
	int		cmd;
	int		q;
	char	c;

	len = 0;
	cmd = 0;
	while (ft_isspace(str[*i + len]))
		len++;
	while ((c = str[*i + len + cmd]) && !ft_strchr("<> ;|", c))
	{
		if (c == '\\')
			cmd++;
		else if ((q = quotation_len(str, *i + len + cmd)) > 0)
			cmd += q;
		else if (q == -1)
			break;
		cmd++;
	}
	if (cmd)
		return (len + cmd);
	*i += len;
	return (0);
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
	if ((len = cmd_len(str, i)) == 0)
		return (str);
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
