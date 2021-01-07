#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <errno.h>

typedef struct      s_env
{
	char			*value;
	struct s_env	*next;
}                   t_env;

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

/*
** env
*/
t_list	*init_env(char **envp);