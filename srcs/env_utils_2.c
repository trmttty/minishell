/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/14 13:48:10 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*find_env(char *env)
{
	t_list	*tmp;

	tmp = g_env_lst;
	while (tmp)
	{
		if (envcmp(tmp->content, env) == 0
			|| envcmp(tmp->content, env) == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			envcmp(const char *env1, const char *env2)
{
	while (*env1 && *env1 != '=' && *env1 == *env2)
	{
		env1++;
		env2++;
	}
	if (*env2 == '+')
		env2++;
	if (*env1 == '\0' && *env2 == '=')
		return (0);
	return (*env1 - *env2);
}

void		sort_env_lst(void)
{
	t_list	*list;
	void	*content;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		list = g_env_lst;
		while (list->next)
		{
			if (envcmp(list->content, list->next->content) > 0)
			{
				content = list->content;
				list->content = list->next->content;
				list->next->content = content;
				swapped = 1;
			}
			list = list->next;
		}
	}
}

static int	env_lst_size(t_list *env_lst)
{
	int		size;
	t_list	*tmp;

	tmp = env_lst;
	size = 0;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '=') != NULL)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

char		**create_env_vec(t_list *env_lst)
{
	char	**env_vec;
	int		size;
	int		i;

	size = env_lst_size(env_lst);
	if ((env_vec = ft_calloc(size + 1, sizeof(char*))) == NULL)
		ft_perror("minishell");
	i = 0;
	while (i < size)
	{
		if (ft_strchr(env_lst->content, '=') != NULL)
		{
			if ((env_vec[i] = ft_strdup(env_lst->content)) == NULL)
				ft_perror("minishell");
			i++;
		}
		env_lst = env_lst->next;
	}
	env_vec[i] = NULL;
	return (env_vec);
}
