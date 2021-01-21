/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/21 18:29:59 by ttarumot         ###   ########.fr       */
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

char		*get_env(char *name)
{
	t_list	*tmp;
	char	**env;
	char	*value;
	
	tmp = g_env_lst;
	value = NULL;
	while (tmp)
	{
		env = ft_split((char*)tmp->content, '=');
		if (ft_strcmp(name, env[0]) == 0) {
			value = ft_strdup(env[1]);
			break;
		}
		tmp = tmp->next;
	}
	ft_tabfree(env);
	if (value != NULL)
		return (value);
	return (ft_strdup(""));
}

char		*replace_env(char *str)
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
	while (str[head])
	{
		if (str[head] != '$')
		{
			while (str[tail] && str[tail] != '$')
				tail++;
			sub = ft_substr(str, head, tail - head);
		}
		else
		{
			tail++;
			while (ft_isalnum(str[tail]) || str[tail] == '_' || str[tail] == '?')
				tail++;
			tmp = ft_substr(str, head, tail - head);
			sub = get_env(&tmp[1]);
			free(tmp);
		}
		size += ft_strlen(sub);
		ret = realloc(ret, (size + 1) * sizeof(char));
		ft_strlcat(ret, sub, size + 1);
		free(sub);
		head = tail;
	}
	return (ret);
}