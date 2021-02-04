/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:10:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/04 15:44:11 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_chdir(char **args)
{
	char	*path;

	if (*args)
	{
		if (chdir(*args) < 0)
			return (1);
	}
	else
	{
		path = get_env("HOME");
		if (chdir(path) < 0)
		{
			free(path);
			return (1);
		}
		free(path);
	}
	return (0);
}

int			ft_cd(char **args)
{
	char	buf[MAXPATHLEN];
	char	*old_pwd;
	char	*new_pwd;

	if (execute_chdir(args))
		return (error_status("cd", *args, strerror(errno), 1));
	old_pwd = get_env("PWD");
	set_env("OLDPWD", old_pwd);
	if (getcwd(buf, MAXPATHLEN))
		set_env("PWD", buf);
	else
	{
		if ((new_pwd = ft_strjoin(old_pwd, "/.")) == NULL)
			ft_perror("minishell");
		set_env("PWD", new_pwd);
		free(new_pwd);
	}
	free(old_pwd);
	return (0);
}
