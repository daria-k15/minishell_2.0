#include "../include/libft.h"

size_t	word_count(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == c)
			count++;
		while (*str == c)
			str++;
		str++;
	}
	return (count);
}

static size_t	ft_len(char const *s, char c, size_t index)
{
	size_t	n;

	n = 0;
	while (s[index + n] != c && s[index + n] != '\0')
		n++;
	return (n);
}

static size_t	ft_skip(char const *s, char c, size_t index)
{
	size_t	i;

	i = index;
	while (s[i] == c)
		i++;
	return (i);
}

int	ft_mfree(char *str, char **arr)
{
	size_t	i;

	i = 0;
	if (str[i] == 0)
	{
		while (i != 0)
			free(arr[i--]);
		free(arr);
		return (0);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**str;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (word_count(s, c) + 2));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		i = ft_skip(s, c, i);
		if (ft_len(s, c, i) != 0)
		{
			str[j] = ft_substr(s, i, ft_len(s, c, i));
			ft_mfree(str[j++], str);
			i = i + ft_len(s, c, i);
		}
	}
	str[j] = NULL;
	return (str);
}
