/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:59:59 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/18 18:52:21 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **args, t_list **env_lst)
{
    t_list *tmp;

    // tmp = *env_lst;
    tmp = g_env_lst;
    while (tmp)
    {
        ft_putendl_fd((char*)(tmp->content), 1);
        tmp = tmp->next;
    }
    return (1);
}
