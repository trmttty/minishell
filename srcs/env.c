/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 02:59:59 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/21 18:43:53 by kazumanoda       ###   ########.fr       */
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
        if (ft_strncmp(tmp->content, "?=", 2) != 0)
            ft_putendl_fd((char*)(tmp->content), 1);
        tmp = tmp->next;
    }
    return (1);
}
