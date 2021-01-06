/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 21:57:01 by ttarumot          #+#    #+#             */
/*   Updated: 2020/07/28 15:42:50 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_word_count(const char *str, char c)
{
	int i;
	int word_count;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			word_count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (word_count);
}

static size_t	ft_get_strlen(const char *str, char c)
{
	size_t len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

char			**ft_split(char const *s, char c)
{
	int		index;
	size_t	len;
	int		word_count;
	char	**list;

	if (!s)
		return (NULL);
	word_count = get_word_count(s, c);
	if (!(list = (char**)ft_calloc(word_count + 1, sizeof(char*))))
		return (NULL);
	index = -1;
	while (++index < word_count)
	{
		while (*s == c && *s)
			s++;
		len = ft_get_strlen(s, c);
		if (!(list[index] = ft_substr(s, 0, len)))
		{
			ft_tabfree(list);
			return (NULL);
		}
		s += len;
	}
	list[index] = NULL;
	return (list);
}
