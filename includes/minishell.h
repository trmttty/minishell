/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:08:44 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/25 22:05:58 by ttarumot         ###   ########.fr       */
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
char	*replace_env(char *str);
char	*remove_quote(char *str);
void	set_env(char *name, char *value);
int		envcmp(const char *env1, const char *env2);

/*
** error
*/
void    exit_with_failure(char *commnad, char *arg, char *message, int code);
int	    return_with_failure(char *commnad, char *arg, char *message, int code);
int		set_exit_status(int code);
void	handle_error(char *message);
#endif
