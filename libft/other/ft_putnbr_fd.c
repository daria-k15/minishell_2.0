#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	nb[11];

	i = 0;
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = n * (-1);
		}
		while (n > 0)
		{
			nb[i++] = n % 10 + 48;
			n = n / 10;
		}
		while (i-- > 0)
			write(fd, &nb[i], 1);
	}
}
