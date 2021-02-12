/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:51:36 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/12 16:06:25 by kazumanoda       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *relative, char **paths)
{
	char		*absolute;
	char		*dir;
	struct stat	sb;

	if ((absolute = ft_strdup("")) == NULL)
		ft_perror("minishell");
	while (*paths)
	{
		if ((dir = ft_strjoin(*paths, "/")) == NULL)
			ft_perror("minishell");
		free(absolute);
		if ((absolute = ft_strjoin(dir, relative)) == NULL)
			ft_perror("minishell");
		free(dir);
		if (stat(absolute, &sb) == 0)
			return (absolute);
		paths++;
	}
	free(absolute);
	return (NULL);
}

char		*get_absolute_path(char *relative)
{
	char		**paths;
	char		*env;
	char		*absolute;

	if (ft_strlen(relative) == 0)
		return (NULL);
	env = get_env("PATH");
	if ((paths = ft_split(env, ':')) == NULL)
		ft_perror("minishell");
	free(env);
	absolute = find_path(relative, paths);
	ft_tabfree(paths);
	return (absolute);
}

int			isdir(char *dir)
{
	DIR		*d;

	if ((d = opendir(dir)))
	{
		closedir(d);
		return (1);
	}
	return (0);
}

int			check_dir(char *dir)
{
	char	*ptr;
	char	*last;
	char	*tmp;
	DIR		*d;

	if (isdir(dir))
		return (error_status(dir, NULL, "is a directory", 126));
	ptr = ft_strchr(dir, '/');
	if ((last = ft_strrchr(dir, '/')) == NULL)
		return (1);
	while (ptr != last)
	{
		ptr++;
		ptr = ft_strchr(ptr, '/');
		tmp = ft_substr(dir, 0, ptr - dir);
		if ((d = opendir(tmp)) == NULL)
		{
			free(tmp);
			return (error_status(dir, NULL, "Not a directory", 126));
		}
		closedir(d);
		free(tmp);
	}
	return (0);
}

int			set_cmd_path(char **args)
{
	char	*absolute;

	if (ft_strcmp(args[0], ".") == 0)
		return (error_status(args[0], "usage", ". filename [arguments]", 127));
	if (ft_strcmp(args[0], "..") == 0)
		return (error_status(args[0], NULL, "command not found", 127));
	if (*args && ft_strchr(*args, '/') == NULL)
	{
		if ((absolute = get_absolute_path(args[0])) == NULL)
			return (error_status(args[0], NULL, "command not found", 127));
		free(args[0]);
		args[0] = absolute;
	}
	return (check_dir(args[0]));
}
