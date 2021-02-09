/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:15:41 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/04 12:28:20 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*cpy;

	cpy = ft_calloc(size, 1);
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, ptr, size);
	free(ptr);
	return (cpy);
}
