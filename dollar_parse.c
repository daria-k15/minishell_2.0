#include "minishell.h"

int	if_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*found_k(char **envp, char *tmp)
{
	int		k;
	int		z;
	char	*tmp2;

	k = 0;
	while (envp[k])
	{
		z = 0;
		while (envp[k][z] && envp[k][z] != '=')
			z++;
		tmp2 = ft_substr(envp[k], 0, z);
		if (ft_strcmp(tmp, tmp2) == 0)
			break ;
		k++;
	}
	tmp2 = ft_substr(envp[k], z + 1, ft_strlen(envp[k]) - z);
	return (tmp2);
}

char	*parse_dollar(char *line, int *i, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp3;
	char	*tmp4;
	char	*res;

	j = *i;
	while (line[++(*i)])
		if (!if_key(line[*i]))
			break ;
	if (*i == j + 1)
		return (line);
	tmp = ft_substr(line, j + 1, *i - j - 1);
	tmp = found_k(envp, tmp);
	tmp3 = ft_substr(line, 0, j);
	tmp4 = ft_substr(line, *i, ft_strlen(line));
	res = ft_strjoin(tmp3, tmp);
	res = ft_strjoin(res, tmp4);
	return (res);
}
