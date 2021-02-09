/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:59:59 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/03 23:28:21 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **args)
{
	t_list	*tmp;

	(void)args;
	sort_env_lst();
	tmp = g_env_lst;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '=') &&
			envcmp(tmp->content, "?=") != 0)
			ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
	return (0);
}
