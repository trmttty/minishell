/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:59:59 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/13 01:43:49 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **args)
{
	t_list	*tmp;

	if (ft_tabsize(args))
		return (0);
	sort_env_lst();
	tmp = g_env_lst;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '=') != NULL)
			ft_putendl_fd(tmp->content, 1);
		tmp = tmp->next;
	}
	return (0);
}
