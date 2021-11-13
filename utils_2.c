#include "minishell.h"

int	ft_strequal(const char *str1, const char *str2)
{
	while ((*str1 == *str2) && *str1 && *str2)
	{	
		str1++;
		str2++;
	}
	return (!((unsigned char)*str1 - (unsigned char)*str2));
}

int	check_redir_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}