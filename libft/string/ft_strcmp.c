#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s1[i] != '\0')
	{
		if (!(s1[i] == s2[i]))
		{
			n = (s1[i] - s2[i]);
			break ;
		}
		i++;
	}
	if (s1[i] == '\0')
	{
		n = s1[i] - s2[i];
	}
	return (n);
}
