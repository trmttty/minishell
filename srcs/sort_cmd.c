#include "minishell.h"
#include <ctype.h>

char	*move_cmd(char *str, int *i, int *argc)
{
	int		len;
	char	*cmd;
	char	*cut;
	char	*tmp;

	len = 0;
	while (isspace(str[*i + len]))
		len++;
	while (str[*i + len] && !ft_strchr("<> ;|", str[*i + len]))
		len++;
	cmd = ft_substr(str, *i, len);
	str[*i] = 0;
	cut = ft_strjoin(str, &str[*i + len]);
	free(str);
	if (*argc == 0)
		str = ft_strjoin(cmd, cut);
	else
	{
		tmp = ft_substr(cut, argc, ft_strlen(cut) - *argc);
		cut[*argc] = 0;
		str = ft_strjoin(cut, cmd);
		free(cut);
		cut = ft_strjoin(str, tmp);
		free(str);
		str = ft_strdup(cut);
		free(tmp);
	}
	*argc += len;
	*i += len;
	free(cmd);
	free(cut);
	return (str);
}

char	*sort_cmd(char *str)
{
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	while (str[i])
	{
		while (ft_strchr(";|", str[i]))
		{
			i++;
			argc = i;
		}
		if (ft_strchr("\'", str[i]))
		{
			i++;
			while (str[i] && !ft_strchr("\'", str[i]))
				i++;
			if (str[i])
				i++;
			else
				break;
		}
		if (ft_strchr("\"", str[i]))
		{
			i++;
			while (str[i] && !ft_strchr("\"", str[i]))
				i++;
			if (str[i])
				i++;
			else
				break;
		}
		if (ft_strchr("<>", str[i]))
		{
			i++;
			//リダイレクションの場合、ポインタを進める
			while (isspace(str[i]))
				i++;
			while (str[i] && !ft_strchr("<> ;|", str[i]))
			{
				if (ft_strchr("\"\'", str[i]))
				{
					break;
				}
				else
				{
					i++;
				}
			}
		}
		else
		{
			move_cmd(str, &i, &argc);
			// //コマンドを切り取り、前に入れ替える
			// int		len = 0;
			// while (isspace(str[i + len]))
			// 	len++;
			// while (str[i + len] && !ft_strchr("<> ;|", str[i + len]))
			// 	len++;
			// char	*cmd;
			// char	*cut;
			// cmd = ft_substr(str, i, len);
			// str[i] = 0;
			// //コマンド切り取り
			// cut = ft_strjoin(str, &str[i + len]);
			// free(str);
			// //コマンドにキューする
			// if (argc == 0)
			// {
			// 	str = ft_strjoin(cmd, cut);
			// }
			// else
			// {
			// 	char	*tmp2 = ft_substr(cut, argc, ft_strlen(cut) - argc);
			// 	cut[argc] = 0;
			// 	str = ft_strjoin(cut, cmd);
			// 	free(cut);
			// 	cut = ft_strjoin(str, tmp2);
			// 	free(str);
			// 	str = ft_strdup(cut);
			// 	free(tmp2);
			// }
			// argc += len;
			// i += len;
			// free(cmd);
			// free(cut);
		}
	}
	return (str);
}
