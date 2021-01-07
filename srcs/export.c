/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/07 21:04:58 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char **args, t_list **env_lst)
{
	t_list	*last;
	t_list	*tmp;

	if (*args)
	{
		tmp = *env_lst;
		while (tmp->next->next)
			tmp = tmp->next;
		last = tmp->next;
		tmp->next = NULL;
		while (*args)
		{
			ft_lstadd_back(env_lst, ft_lstnew(ft_strdup(*args)));
			args++;
		}
		ft_lstadd_back(env_lst, last);
	}
	return (1);
}