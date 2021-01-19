/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:08:44 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/20 00:37:23 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>	
#include <sys/types.h>

typedef struct      s_env
{
	char			*value;
	struct s_env	*next;
}                   t_env;

t_list	*g_env_lst;
/*
** builtin
*/
int     ft_echo(char **args, t_list **env_lst);
int     ft_cd(char **args, t_list **env_lst);
int		ft_pwd(char **args, t_list **env_lst);
int     ft_export(char **args, t_list **env_lst);
int     ft_unset(char **args, t_list **env_lst);
int     ft_env(char **args, t_list **env_lst);
int     ft_exit(char **args, t_list **env_lst);

int		launch(char **args);
void	loop(t_list **env_lst);

/*
** env
*/
t_list	*init_env(char **envp);
char	*get_env(char *key);

#endif
