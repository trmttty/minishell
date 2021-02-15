/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 09:46:08 by ttarumot          #+#    #+#             */
/*   Updated: 2021/02/15 11:59:37 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

static void		reset_remain(char **remain)
{
	if (*remain)
	{
		free(*remain);
		*remain = NULL;
	}
}

static int		read_remain(char **line, char **remain, char **newline)
{
	char *tmp;

	**newline = '\0';
	if (!(*line = ft_strdup(*remain)))
	{
		reset_remain(remain);
		return (-1);
	}
	tmp = *remain;
	*remain = ft_strdup(*newline + 1);
	free(tmp);
	return (*remain == NULL ? -1 : 1);
}

static ssize_t	read_fd_while(int fd, char **remain, char **newline)
{
	char	*buf;
	char	*tmp;
	ssize_t	ret;

	if ((buf = (char*)malloc(BUFFER_SIZE + 1)) == NULL)
		ft_perror("minishell");
	while (!*newline && ((ret = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n') == NULL)
			ft_putstr_fd("  \b\b", 2);
		tmp = remain[fd];
		if (!(remain[fd] = ft_strjoin(remain[fd], buf)))
			ret = -1;
		free(tmp);
		*newline = ft_strchr(remain[fd], '\n');
	}
	free(buf);
	return (ret);
}

static int		read_fd(int fd, char **line, char **remain, char **newline)
{
	ssize_t	ret;

	ret = read_fd_while(fd, remain, newline);
	if (ft_strlen(*remain))
	{
		ft_putstr_fd("  \b\b", 2);
		return (get_next_line(0, line));
	}
	if (ret != -1 && *newline)
		return (read_remain(line, &remain[fd], newline));
	if (ret != -1 && !(*line = ft_strdup(remain[fd])))
		ret = -1;
	reset_remain(&remain[fd]);
	return (ret == -1 ? -1 : 0);
}

int				get_next_line(int fd, char **line)
{
	static char	*remain[FD_MAX];
	char		*newline;

	if (fd < 0 || line == NULL || fd > FD_MAX)
		return (-1);
	if (!remain[fd])
	{
		if (!(remain[fd] = ft_strdup("")))
			return (-1);
	}
	if ((newline = ft_strchr(remain[fd], '\n')))
		return (read_remain(line, &remain[fd], &newline));
	return (read_fd(fd, line, remain, &newline));
}
