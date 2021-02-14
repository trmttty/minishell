/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/14 20:48:44 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*value_with_escape(char *value)
{
	size_t	len;
	size_t	escape;
	size_t	i;
	size_t	j;
	char	*ret;

	len = ft_strlen(value);
	i = 0;
	escape = 0;
	while (value[i])
	{
		if (ft_strchr("\\\"$`", value[i]))
			escape++;
		i++;
	}
	if ((ret = ft_calloc(len + escape, sizeof(char))) == NULL)
		ft_perror("minishell");
	i = 0;
	j = 0;
	while (i < len + escape)
	{
		if (ft_strchr("\\\"$`", value[j]))
			ret[i++] = '\\';
		ret[i] = value[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

int			ft_declare(void)
{
	t_list	*list;
	char	*name;
	char	*value;
	char	*equal;

	sort_env_lst();
	list = g_env_lst;
	while (list)
	{
		if (envcmp(list->content, "_=") != 0)
		{
			if ((equal = ft_strchr(list->content, '=')))
			{
				if ((name = ft_substr(list->content, 0,
					equal - (char*)list->content)) == NULL)
					ft_perror("minishell");
				value = value_with_escape(++equal);
				printf("declare -x %s=\"%s\"\n", name, value);
				free(name);
				free(value);
			}
			else
				printf("declare -x %s\n", list->content);
		}
		list = list->next;
	}
	return (1);
}
