/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:08:44 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/05 08:41:37 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
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
extern	char **environ;
/*
** builtin
*/
int     ft_echo(char **args);
int     ft_cd(char **args);
int		ft_pwd(char **args);
int     ft_export(char **args);
int     ft_unset(char **args);
int     ft_env(char **args);
int     ft_exit(char **args);

int		launch(char **args);
void	loop(void);

/*
** env
*/
t_list	*init_env(char **envp);
char	*get_env(char *key);
char	*replace_env(char *str);
char	*remove_quote(char *str);
int		set_env(char *name, char *value);
int		envcmp(const char *env1, const char *env2);
void	sort_env_lst(void);
t_list	*find_env(char *env);

/*
** error
*/
void    exit_status(char *commnad, char *arg, char *message, int code);
int	    error_status(char *commnad, char *arg, char *message, int code);
int		set_exit_status(int code);
void	ft_perror(char *message);

/*
** realloc
*/
void	*ft_realloc(void *ptr, size_t size);

#endif
