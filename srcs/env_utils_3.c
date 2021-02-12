/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:46:03 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/13 01:43:23 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
