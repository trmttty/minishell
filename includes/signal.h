/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 00:01:14 by ttarumot          #+#    #+#             */
/*   Updated: 2021/01/20 00:12:23 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H 
# define SIGNAL_H 

# include <signal.h>

void	parent_sigint(int sig);
void	child_sigint(int sig);

#endif