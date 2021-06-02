#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

# include <stdio.h>
# include <signal.h>

static char	*ft_charjoin(char *line, char const c)
{
	size_t	len;
	char	*str;

	len = ft_strlen(line) + 1;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		exit_shell(errno);
	ft_strlcpy(str, line, len);
	str[len - 1] = c;
	free(line);
	return (str);
}

ssize_t	read_line(char **line)
{
	ssize_t	ret;
	ssize_t	len;
	char	buf;

	ret = 1;
	len = 0;
	buf = 0;
	*line = (char *)ft_calloc(1, sizeof(char));
	while (line && ret > 0)
	{
		ret = read(0, &buf, 1);
		if (ret == 0 && len == 0)
		{
			printf("exit\n");
			break ;
		}
		if (ret == -1)
			exit_shell(errno);
		*line = ft_charjoin(*line, buf);
		len += ret;
		if (buf == '\n')
			break ;
	}
	if (errno)
		exit_shell(errno);
	return (len);
}
