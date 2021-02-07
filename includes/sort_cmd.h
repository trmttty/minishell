/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 22:07:17 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/07 14:36:31 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_CMD_H
# define SORT_CMD_H

int		ft_isspace(char c);
int		cmd_len(char *str, int *i);
int		skip_quotation(char *str, int i);
int		skip_redirection(char *str, int i);
char	*move_cmd(char *str, int *i, int *argc);
char	*sort_cmd(char *str);

# define CMD 0
# define CUT 1
# define LHS 2
# define RHS 3

#endif
