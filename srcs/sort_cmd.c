#include "minishell.h"
#include <ctype.h>

//aim
//		> lol echo test lol
//		echo test lol > lol

//		>lol echo > test>lol>test>>lol>test mdr >lol test >test
//		echo mdr test>lol> test>lol>test>>lol>test >lol >test

char	*sort_cmd(char *str)
{
	int		i;
	int		argc;
	char	**parts;

	i = 0;
	argc = 0;
	parts = (char **)ft_calloc(ft_strlen(str), sizeof(char *));
	while (str[i])
	{
		if (ft_strchr(";|", str[i]))
		{
			i++;
			argc = i;
		}
		if (ft_strchr("<>", str[i]))
		{
			i++;
			//リダイレクションの場合、ポインタを進める
			while (isspace(str[i]))
				i++;
			while (!ft_strchr("<> ;|", str[i]))
			{
				if (ft_strchr("\"\'", str[i]))
				{
					//ダブルクオーテーションが来るまでスキップ
					while (!ft_strchr("\"\'", str[i]))
						i++;
				}
				i++;
			}
		}
		else
		{
			//コマンドを切り取り、前に入れ替える
			int		len = 0;
			while (isspace(str[i + len]))
				len++;
			while (str[i + len] && !ft_strchr("<> ;|", str[i + len]))
				len++;
			char	*cmd;
			char	*tmp;
			cmd = ft_substr(str, i, len);
			str[i] = 0;
			//コマンド切り取り
			tmp = ft_strjoin(str, &str[i + len]);
			free(str);
			//コマンドにキューする
			if (argc == 0)
			{
				str = ft_strjoin(cmd, tmp);
			}
			else
			{
				char	*tmp2 = ft_substr(tmp, argc, ft_strlen(tmp) - argc);
				tmp[argc] = 0;
				str = ft_strjoin(tmp, cmd);
				tmp = ft_strjoin(str, tmp2);
				str = tmp;
			}
			argc += len;
			i += len;
		}
	}
	return (str);
}
