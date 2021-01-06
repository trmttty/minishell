/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:16:25 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 09:17:04 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_atof(char *str)
{
	double	ret1;
	double	ret2;
	int		len;

	ret1 = (double)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	ret2 = (double)ft_atoi(str);
	len = ft_strlen(str);
	while (len--)
		ret2 /= 10;
	return (ret1 + ((ret1 >= 0) ? ret2 : -ret2));
}
