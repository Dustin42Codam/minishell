#include "minishell.h"
#include "libft.h"
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

void	minishell_putstr(const char *str)
{
	const int	write_failed = -1;
	int			size;

	size = ft_strlen(str);
	if (write(1, str, size) == write_failed)
		exit_minishell(errno);
}
