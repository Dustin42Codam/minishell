#include "minishell.h"
#include <unistd.h>
#include <errno.h>

ssize_t	minishell_write(int fd, const void *buf, size_t count)
{
	ssize_t	ret;

	ret = write(fd, buf, count);
	if (ret == -1)
		exit_minishell(errno);
	return (ret);
}
