/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:10:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/25 22:19:34 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char **args, t_list **env_lst)
{
	char	*path;
    char	buf[MAXPATHLEN];
	char	*old_pwd;
	char	*new_pwd;

	if (*args)
		path = *args;
	else
		path = get_env("HOME");
	if (chdir(path) < 0)
		return (return_with_failure("cd", *args, strerror(errno), 1));
	old_pwd = get_env("PWD");
	set_env("OLDPWD", old_pwd);
	if (getcwd(buf, MAXPATHLEN))
		set_env("PWD", buf);
	else
	{
		new_pwd = ft_strjoin(old_pwd, "/.");
		set_env("PWD", new_pwd);
		free(new_pwd);
	}
	free(old_pwd);
	return (0);
}
