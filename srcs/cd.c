/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:10:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/11 15:13:05 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*execute_chdir(char **args)
{
	char	*path;

	if (*args)
	{
		if (chdir(*args) < 0)
			return (strerror(errno));
	}
	else
	{
		path = get_env("HOME");
		if (ft_strlen(path) == 0)
		{
			free(path);
			return ("HOME not set");
		}
		if (chdir(path) < 0)
		{
			free(path);
			return (strerror(errno));
		}
		free(path);
	}
	return (NULL);
}

int			ft_cd(char **args)
{
	char	buf[MAXPATHLEN];
	char	*message;
	char	*old_pwd;
	char	*new_pwd;

	if ((message = execute_chdir(args)) != NULL)
		return (error_status("cd", *args, message, 1));
	old_pwd = get_env("PWD");
	if (find_env("OLDPWD"))
		set_env("OLDPWD", old_pwd);
	if (getcwd(buf, MAXPATHLEN) && find_env("PWD"))
		set_env("PWD", buf);
	else
	{
		if ((new_pwd = ft_strjoin(old_pwd, "/.")) == NULL)
			ft_perror("minishell");
		if (find_env("PWD"))
			set_env("PWD", new_pwd);
		free(new_pwd);
		free(old_pwd);
		return (error_status("cd", "getcwd", strerror(errno), 0));
	}
	free(old_pwd);
	return (0);
}
