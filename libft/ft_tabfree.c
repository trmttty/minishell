/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 15:39:43 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/03 11:31:06 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_tabfree(char **tab)
{
	char **tmp;

	if (!tab)
		return ;
	tmp = tab;
	while (*tmp)
		free(*tmp++);
	free(tab);
}
