/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:59:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/03 23:33:31 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b\n> ", 1);
}

void	child_sigint(int sig)
{
	(void)sig;
}

void	parent_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b", 1);
}
