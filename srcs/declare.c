/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:55:33 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 12:21:16 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_escape(char *value)
{
	size_t	i;
	size_t	escape;

	i = 0;
	escape = 0;
	while (value[i])
	{
		if (ft_strchr("\\\"$`", value[i]))
			escape++;
		i++;
	}
	return (escape);
}

static char	*value_with_escape(char *value)
{
	size_t	len;
	size_t	escape;
	size_t	i;
	size_t	j;
	char	*ret;

	len = ft_strlen(value);
	escape = count_escape(value);
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

static void	print_declare(t_list *list)
{
	char	*name;
	char	*value;
	char	*equal;

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

int			ft_declare(void)
{
	t_list	*list;

	sort_env_lst();
	list = g_env_lst;
	while (list)
	{
		if (envcmp(list->content, "_=") != 0)
			print_declare(list);
		list = list->next;
	}
	return (1);
}
