/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/08 14:09:32 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char		**create_env_vec(t_list *env_lst)
{
	char	**env_vec;
	int		size;
	int		i;

	size = ft_lstsize(env_lst);
	if ((env_vec = ft_calloc(size + 1, sizeof(char*))) == NULL)
		ft_perror("minishell");
	i = 0;
	while (i < size)
	{
		if ((env_vec[i] = ft_strdup(env_lst->content)) == NULL)
			ft_perror("minishell");
		i++;
		env_lst = env_lst->next;
	}
	env_vec[i] = NULL;
	return (env_vec);
}
