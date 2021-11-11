#include "libft.h"

static int	ft_num(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	i = ft_num(n);
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	res[i] = '\0';
	i--;
	if (n < 0)
	{
		res[0] = '-';
		n = n * (-1);
	}
	while (n > 0)
	{
		res[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (res);
}
