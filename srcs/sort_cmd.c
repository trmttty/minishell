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
			// fprintf(stderr, "++ : i=%d, argc=%d\n", i, argc);
		}
		if (ft_strchr("<>", str[i]))
		{
			// fprintf(stderr, "if >> %d\n", i);
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
			// fprintf(stderr, "else: i=%d, argc=%d\n", i, argc);
			// fprintf(stderr, "elsestr >> %s\n", &str[i]);
			//コマンドを切り取り、前に入れ替える
			int		len = 0;
			while (isspace(str[i + len]))
				len++;
			while (str[i + len] && !ft_strchr("<> ;|", str[i + len]))
			{
				len++;
			}
			// fprintf(stderr, "len >> %d\n", len);
			char	*cmd;
			char	*tmp;
			cmd = ft_substr(str, i, len);
			// fprintf(stderr, "cmd -%s-\n", cmd);
			str[i] = 0;
			//コマンド切り取り
			tmp = ft_strjoin(str, &str[i + len]);
			// fprintf(stderr, "tmp -%s-\n", tmp);
			free(str);
			//コマンドにキューする
			if (argc == 0)
			{
				str = ft_strjoin(cmd, tmp);
			}
			else
			{
				char	*tmp2 = ft_substr(tmp, argc, ft_strlen(tmp) - argc);
				// fprintf(stderr, "tmp2 -%s-\n", tmp2);
				tmp[argc] = 0;
				str = ft_strjoin(tmp, cmd);
				tmp = ft_strjoin(str, tmp2);
				str = tmp;
			}
			argc += len;
			i += len;
			// fprintf(stderr, "i >> %d\n", i);
			// fprintf(stderr, "str -%s-\n", str);
		}
	}
	return (str);
}
