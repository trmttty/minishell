/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 03:24:43 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/07 17:34:47 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(char **args, t_list **env_lst)
{
    char    buf[MAXPATHLEN];

    if (getcwd(buf, MAXPATHLEN))
    {
        ft_putendl_fd(buf, 1);
        return (1);
    }
    return (0);
}
