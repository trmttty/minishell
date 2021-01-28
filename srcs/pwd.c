/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 03:24:43 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/29 01:53:26 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(char **args, t_list **env_lst)
{
	char    *path;

	path = get_env("PWD");
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
