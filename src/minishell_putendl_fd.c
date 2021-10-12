#include "minishell.h"
#include <unistd.h>

ssize_t	minishell_putendl_fd(const char *s, int fd)
{
	ssize_t	ret;

	ret = minishell_putstr_fd(s, fd);
	ret += minishell_write(fd, "\n", 1);
	return (ret);
}
