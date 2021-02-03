/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:10:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/03 23:18:18 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char **args)
{
	char	*path;
	char	buf[MAXPATHLEN];
	char	*old_pwd;
	char	*new_pwd;

	if (*args)
	{
		if (chdir(*args) < 0)
			return (return_failure("cd", *args, strerror(errno), 1));
	}
	else
	{
		path = get_env("HOME");
		if (chdir(path) < 0)
		{
			free(path);
			return (return_failure("cd", *args, strerror(errno), 1));
		}
		free(path);
	}
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
