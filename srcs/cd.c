/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:10:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/22 22:09:16 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char **args, t_list **env_lst)
{
	char	*path;
    char    buf[MAXPATHLEN];

	if (*args)
		path = *args;
	else
		path = get_env("HOME");
	if (chdir(path) < 0)
	{
		return (return_with_failure("cd", *args, strerror(errno), 0));
	}
    if (getcwd(buf, MAXPATHLEN))
        set_env("PWD", buf);
	return (1);
}
