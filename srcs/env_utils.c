/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/29 02:01:02 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*init_env(char **envp)
{
	t_list	*env_lst;

	env_lst = NULL;
	while (*envp)
	{
		ft_lstadd_back(&env_lst, ft_lstnew(ft_strdup(*envp)));
		envp++;
	}
	return (env_lst);
}

int		envcmp(const char *env1, const char *env2)
{
	while (*env1 && *env1 != '=' && *env1 == *env2)
	{
		env1++;
		env2++;
	}
	if (*env2 == '+')
		env2++;
	return (*env1 - *env2);
}

char		*get_env(char *name)
{
	t_list	*tmp;
	char	*value;
	char	*env;
	
	if ((env = ft_strjoin(name, "=")) == NULL)
		ft_perror("minishell");
	tmp = g_env_lst;
	while (tmp)
	{
		if (envcmp(tmp->content, env) == 0)
		{
			if ((value = ft_strdup(ft_strchr(tmp->content, '=') + 1)) == NULL)
				ft_perror("minishell");
			free(env);
			return (value);
		}
		tmp = tmp->next;
	}
	free(env);
	if ((value = ft_strdup("")) == NULL)
		ft_perror("minishell");
	return (value);
}

int			set_env(char *name, char *value)
{
	char	*tmp;
	char	*env;
	char	**arg;

	if ((tmp = ft_strjoin(name, "=")) == NULL)
		ft_perror("minishell");
	if ((env = ft_strjoin(tmp, value)) == NULL)
		ft_perror("minishell");
	free(tmp);
	if ((arg = ft_split(env, ' ')) == NULL)
		ft_perror("minishell");
	ft_export(arg ,&g_env_lst);
	free(env);
	ft_tabfree(arg);
	return (0);
}

char		*replace_env(char *str)
{
	char	*ret;
	size_t	size;
	size_t	head;
	size_t	tail;
	char	*tmp;
	char	*sub;

	if ((ret = ft_strdup("")) == NULL)
		ft_perror("minishell");
	head = 0;
	tail = 0;
	size = 0;
	while (str[tail])
	{
		if (str[tail] == '\\' && str[tail + 1] == '$')
		{
			head += 1;
			tail += 2;
		}
		if (str[tail] != '$')
		{
			while (str[tail] && str[tail] != '$')
				tail++;
			sub = ft_substr(str, head, tail - head);
		}
		else
		{
			tail++;
			if (str[tail] >= '0' && str[tail] <= '9')
			{
				tail++;
				head = tail;
				continue;
			}
			else
			{
				while (ft_isalnum(str[tail]) || str[tail] == '_')
					tail++;
				if (str[tail] == '?')
					tail++;
				if (tail - head == 1) 
					sub = ft_substr(str, head, tail - head);
				else
				{
					tmp = ft_substr(str, head, tail - head);
					sub = get_env(&tmp[1]);
					free(tmp);
				}
			}
		}
		size += ft_strlen(sub);
		ret = realloc(ret, (size + 1) * sizeof(char));
		ft_strlcat(ret, sub, size + 1);
		free(sub);
		head = tail;
	}
	return (ret);
}

char		*remove_quote(char *str)
{
	char	*ret;
	size_t	size;
	size_t	head;
	size_t	tail;
	char	*tmp;
	char	*sub;

	ret = ft_strdup("");
	head = 0;
	tail = 0;
	size = 0;
	while (str[tail])
	{
		if (str[tail] == '\\')
		{
			head += 1;
			tail += 2;
		}
		if (str[tail] != '"')
		{
			while (str[tail] && str[tail] != '"')
				tail++;
			sub = ft_substr(str, head, tail - head);
		}
		else
		{
			head++;
			tail++;
			while (str[tail] && str[tail] != '"')
				tail++;
			sub = ft_substr(str, head, tail - head);
		}
		size += ft_strlen(sub);
		ret = realloc(ret, (size + 1) * sizeof(char));
		ft_strlcat(ret, sub, size + 1);
		free(sub);
		head = tail;
	}
	return (ret);
}
