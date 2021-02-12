/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 21:20:00 by kazumanoda        #+#    #+#             */
/*   Updated: 2021/02/12 11:11:43 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "evaluate.h"

int		create_fd(t_node *node, int *flag)
{
	int		ret;
	int		fd;

	if (node->lnode->operation && ft_strchr("<>", *node->lnode->operation))
	{
		ret = create_fd(node->lnode, flag);	
		if (ret == -1)
			return (-1);
	}
	if (node->operation && ft_strcmp(">", node->operation) == 0)
	{
		if ((fd = open(node->rnode->commands[0], \
			O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		{
			return(error_status(NULL, node->rnode->commands[0],
								strerror(errno), -1));
		}
		close(fd);
	}	
	else if (node->operation && ft_strcmp(">>", node->operation) == 0)
	{
		if ((fd = open(node->rnode->commands[0], \
			O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
		{
			return(error_status(NULL, node->rnode->commands[0],
								strerror(errno), -1));
		}
		close(fd);
	}
	else if (node->operation && ft_strcmp("<", node->operation) == 0)
	{
		if ((fd = open(node->rnode->commands[0], O_RDONLY)) == -1)
		{
			return(error_status(NULL, node->rnode->commands[0],
								strerror(errno), -1));
		}
		close(fd);
	}
	return (1);
}

int		ft_redirect_out(t_node *node, int *flag)
{
	int		fd;
	int		tmp;
	int		ret;

	// if (node->lnode->operation && ft_strchr("<>", *node->lnode->operation))
	// {
	// 	ret = create_fd(node->lnode, flag);
	// 	if (ret == -1)
	// 		return (1);
	// }
	if ((fd = open(node->rnode->commands[0], \
		O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		return(error_status(NULL, node->rnode->commands[0],
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

int		ft_redirect_outout(t_node *node, int *flag)
{
	int		fd;
	int		tmp;
	int		ret;

	// if (node->lnode->operation && ft_strchr("<>", *node->lnode->operation))
	// {
	// 	ret = create_fd(node->lnode, flag);
	// 	if (ret == -1)
	// 		return (1);
	// }
	if ((fd = open(node->rnode->commands[0], \
		O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
	{
		return(error_status(NULL, node->rnode->commands[0],
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

int		ft_redirect_in(t_node *node, int *flag)
{
	int		fd;
	int		tmp;
	int		ret;

	// if (node->lnode->operation && ft_strchr("<>", *node->lnode->operation))
	// {
	// 	ret = create_fd(node->lnode, flag);
	// 	if (ret == -1)
	// 		return (1);
	// }
	if ((fd = open(node->rnode->commands[0], O_RDONLY)) == -1)
	{
		return(error_status(NULL, node->rnode->commands[0],
							strerror(errno), 1));
	}
	tmp = dup(STDIN_FILENO);
	if (flag[1] == 0)
	{
		dup2(fd, STDIN_FILENO);
		flag[1] = 1;
	}
	close(fd);
	ret = evaluate(node->lnode, flag);
	dup2(tmp, STDIN_FILENO);
	close(tmp);
	return (ret);
}
