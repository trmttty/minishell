/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:59:59 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/23 00:57:09 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **args, t_list **env_lst)
{
	t_list  *tmp;

	// tmp = *env_lst;
	tmp = g_env_lst;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '=') &&
			envcmp(tmp->content, "?=") != 0)
			ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
	return (1);
}
