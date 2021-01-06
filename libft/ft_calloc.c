/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 13:18:41 by ttarumot          #+#    #+#             */
/*   Updated: 2020/06/30 11:05:52 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *ptr;

	if ((ptr = malloc(count * size)) == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
