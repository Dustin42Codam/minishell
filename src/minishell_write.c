#include "minishell.h"
#include <unistd.h>
#include <errno.h>

ssize_t	minishell_write(int fd, const void *buf, size_t count)
{
	const int	write_failed = -1;
	ssize_t		ret;

	ret = write(fd, buf, count);
	if (ret == write_failed)
		exit_minishell(errno);
	return (ret);
}
