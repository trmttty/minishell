/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:08:44 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/11 22:26:11 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct		s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

t_list				*g_env_lst;

/*
** main
*/
int					ft_iswspace_str(char *str);
int					set_exit_status(int status);
int					launch(char **args);

/*
** builtin
*/
int					ft_echo(char **args);
int					ft_cd(char **args);
int					ft_pwd(char **args);
int					ft_export(char **args);
int					ft_export_question(char **args);
int					ft_unset(char **args);
int					ft_env(char **args);
int					ft_exit(char **args);
int					launch(char **args);

/*
** env
*/
t_list				*init_env_lst(char **envp);
void				init_env(char *arg);
char				*get_env(char *key);
char				*replace_env(char *str);
char				*remove_quote(char *str);
int					set_env(char *name, char *value);
int					set_question(char *name, char *value);
int					envcmp(const char *env1, const char *env2);
void				sort_env_lst(void);
t_list				*find_env(char *env);
char				**create_env_vec(t_list *env_lst);
void				update_env(char *arg);
void				add_env(char *arg);

/*
** error
*/
void				exit_status(char *commnad, char *arg, \
								char *message, int code);
int					error_status(char *commnad, char *arg, \
								char *message, int code);
int					set_exit_status(int code);
void				ft_perror(char *message);

/*
** realloc
*/
void				*ft_realloc(void *ptr, size_t size);

/*
** set_cmd_path
*/
int					set_cmd_path(char **args);

# define INT_STATUS 130
# define QUIT_STATUS 131

#endif
