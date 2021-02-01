/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazumanoda <kazumanoda@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 21:15:41 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/01 21:21:39 by kazumanoda       ###   ########.fr       */
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
	return (cpy);
}
