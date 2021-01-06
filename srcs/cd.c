/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:10:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/07 03:03:41 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char **args, char **envp)
{
	if (chdir(args[0]) < 0)
		ft_putendl_fd(strerror(errno), 2);
	return (1);
}