#include "../include/libft.h"

static int	index_search(const char *str, int ch)
{
	size_t	i;

	i = 0;
	while (str[i] != ch && str[i])
		i++;
	if (str[i] == (char)ch)
		return (i);
	return (-1);
}

static int	get_line(char **line, char *buf)
{
	int	i;

	i = index_search(buf, '\n');
	*line = ft_substr(buf, 0, i);
	++i;
	ft_memcpy(buf, buf + i, (ft_strlen(buf + i) + 1));
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf;
	char		tmp[BUFFER_SIZE + 1];
	int			bytes;

	bytes = 1;
	if (fd < 0 || !line || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
		return (-1);
	while (bytes > 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		tmp[bytes] = '\0';
		buf = ft_strjoinf(buf, tmp);
		if (index_search(buf, '\n') != -1)
			return (get_line(line, buf));
	}
	if (buf)
	{
		*line = ft_strdup(buf);
		free(buf);
		buf = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (1);
}
