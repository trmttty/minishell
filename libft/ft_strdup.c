/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 13:36:34 by ttarumot          #+#    #+#             */
/*   Updated: 2020/06/30 12:20:25 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	size;
	char	*ptr;

	size = ft_strlen(src) + 1;
	if (!(ptr = (char*)malloc(sizeof(char) * size)))
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(ptr, src, size);
	return (ptr);
}
