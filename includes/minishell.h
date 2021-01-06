#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <errno.h>

int     ft_echo(char **args, char **envp);
int     ft_cd(char **args, char **envp);
int		ft_pwd(char **args, char **envp);
int     ft_env(char **args, char **envp);
int     ft_exit(char **args, char **envp);