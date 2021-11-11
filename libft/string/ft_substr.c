#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = start;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (i < len)
		{
			dst[i] = s[j];
			i++;
			j++;
		}
	}
	dst[i] = '\0';
	return (dst);
}
