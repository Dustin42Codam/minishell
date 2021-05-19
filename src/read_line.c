#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

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

char	*read_line(void)
{
	char	*line;
	char	buf;
	ssize_t	ret;

	line = ft_calloc(1, 1);
	buf = 0;
	ret = 1;
	while (line && ret > 0 && buf != '\n')
	{
		ret = read(0, &buf, 1);
		if (ret == 0 && ft_strlen(line) == 0)
			exit(0);
		else if (ret == -1)
			exit_shell(errno);
		line = ft_charjoin(line, buf);
	}
	if (errno)
		exit_shell(errno);
	return (line);
}
