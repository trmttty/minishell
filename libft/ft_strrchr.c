/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:18:16 by ttarumot          #+#    #+#             */
/*   Updated: 2020/06/30 10:23:03 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ret;

	c = (char)c;
	ret = NULL;
	while (*s)
	{
		if (*s == c)
			ret = (char*)s;
		s++;
	}
	if (*s == c)
		ret = (char*)s;
	return (ret);
}
