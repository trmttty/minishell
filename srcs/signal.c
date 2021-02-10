/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:59:48 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/10 09:11:23 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\033[0;36m\033[1m\b\b  \b\b\nminishell ▸ \033[0m", 2);
	set_question("?", "1");
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
