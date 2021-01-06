/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 01:13:23 by ttarumot          #+#    #+#             */
/*   Updated: 2020/06/30 11:44:38 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digit(unsigned int nb)
{
	size_t digit;

	digit = 0;
	while (nb / 10)
	{
		digit++;
		nb /= 10;
	}
	return (digit);
}

static void		set_nbr(char *ret, unsigned int nb, int len, int sign)
{
	if (sign == -1)
	{
		*ret++ = '-';
		len--;
	}
	ret += len;
	*ret-- = '\0';
	while (len--)
	{
		*ret-- = nb % 10 + '0';
		nb /= 10;
	}
}

char			*ft_itoa(int n)
{
	unsigned int	nb;
	size_t			len;
	int				sign;
	char			*ret;

	len = 1;
	sign = 1;
	if (n < 0)
	{
		len++;
		sign = -1;
		nb = -n;
	}
	else
		nb = n;
	len += get_digit(nb);
	if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	set_nbr(ret, nb, len, sign);
	return (ret);
}
