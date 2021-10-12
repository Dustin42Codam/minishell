#include "minishell.h"
#include <unistd.h>

ssize_t	minishell_putchar_fd(const char c, int fd)
{
	return (minishell_write(fd, &c, 1));
}
