/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:20:00 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/12 14:10:43 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

static int	create_file(t_node *node, int *flag)
{
	int		fd;
	char	*file_name;

	file_name = node->rnode->commands[0];
	if (file_name == NULL || (file_name && ft_strlen(file_name) == 0))
		return (error_status(NULL, NULL, "ambiguous redirect", -1));
	if (ft_strcmp(">", node->operation) == 0)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strcmp(">>", node->operation) == 0)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strcmp("<", node->operation) == 0)
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (error_status(NULL, file_name, strerror(errno), -1));
	close(fd);
	return (1);
}

int			create_redirect(t_node *node, int *flag)
{
	if (node->lnode->operation && ft_strchr("<>", *node->lnode->operation))
	{
		if (create_redirect(node->lnode, flag) == -1)
			return (-1);
	}
	if (node->operation && ft_strchr("<>", *node->operation))
		return (create_file(node, flag));
	return (1);
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
