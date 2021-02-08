/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 03:24:43 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/08 22:15:07 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(char **args)
{
	char	buf[MAXPATHLEN];
	char	*path;

	(void)args;
	if (getcwd(buf, MAXPATHLEN))
		ft_putendl_fd(buf, 1);
	else
	{
		path = get_env("PWD");
		ft_putendl_fd(path, 1);
		free(path);
	}
	return (0);
}
