/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 00:23:51 by ttarumot          #+#    #+#             */
/*   Updated: 2020/06/26 23:31:10 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;
	unsigned char		uc;

	d = dst;
	uc = c;
	while (n--)
	{
		*d++ = *s;
		if (uc == *s)
			return (d);
		s++;
	}
	return (NULL);
}
