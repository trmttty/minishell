/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:20:00 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/13 22:59:41 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"
#include "lexer.h"

static int	create_file(t_node *node)
{
	int		fd;
	char	**commands;

	commands = lexer_expand_command(node->rnode->commands);
	node->expand = 1;
	fd = 0;
	if (ft_tabsize(commands) != 1 || (*commands && ft_strlen(*commands) == 0))
	{
		ft_tabfree(commands);
		return (error_status(NULL, *node->rnode->commands, "ambiguous redirect", 1));
	}
	if (ft_strcmp(">", node->operation) == 0)
		fd = open(*commands, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strcmp(">>", node->operation) == 0)
		fd = open(*commands, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strcmp("<", node->operation) == 0)
		fd = open(*commands, O_RDONLY);
	ft_tabfree(node->rnode->commands);
	node->rnode->commands = commands;
	if (fd == -1)
		return (error_status(NULL, *commands, strerror(errno), 1));
	close(fd);
	return (0);
}

int			create_redirect(t_node *node, int *flag)
{
	if (node->expand)
		return (0);
	if (node->lnode->operation && ft_strchr("<>", *node->lnode->operation))
	{
		if (create_redirect(node->lnode, flag) == -1)
			return (1);
	}
	if (node->operation && ft_strchr("<>", *node->operation))
		return (create_file(node));
	return (0);
}

int			ft_redirect_out(t_node *node, int *flag)
{
	int		fd;
	int		tmp;
	int		ret;

	if ((fd = open(node->rnode->commands[0], \
		O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		return (error_status(NULL, node->rnode->commands[0],
							strerror(errno), 1));
	}
	tmp = dup(STDOUT_FILENO);
	if (flag[1] == 0)
	{
		dup2(fd, STDOUT_FILENO);
		flag[1] = 1;
	}
	close(fd);
	ret = evaluate(node->lnode, flag);
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	return (ret);
}

int			ft_redirect_outout(t_node *node, int *flag)
{
	int		fd;
	int		tmp;
	int		ret;

	if ((fd = open(node->rnode->commands[0], \
		O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
	{
		return (error_status(NULL, node->rnode->commands[0],
							strerror(errno), 1));
	}
	tmp = dup(STDOUT_FILENO);
	if (flag[1] == 0)
	{
		dup2(fd, STDOUT_FILENO);
		flag[1] = 1;
	}
	close(fd);
	ret = evaluate(node->lnode, flag);
	dup2(tmp, STDOUT_FILENO);
	close(tmp);
	return (ret);
}

int			ft_redirect_in(t_node *node, int *flag)
{
	int		fd;
	int		tmp;
	int		ret;

	if ((fd = open(node->rnode->commands[0], O_RDONLY)) == -1)
	{
		return (error_status(NULL, node->rnode->commands[0],
							strerror(errno), 1));
	}
	tmp = dup(STDIN_FILENO);
	if (flag[0] == 0)
	{
		dup2(fd, STDIN_FILENO);
		flag[0] = 1;
	}
	close(fd);
	ret = evaluate(node->lnode, flag);
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	return (ret);
}
