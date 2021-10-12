#include "minishell.h"
#include "libft.h"
#include <unistd.h>

ssize_t	minishell_putstr_fd(const char *str, int fd)
{
	return (minishell_write(fd, str, ft_strlen(str)));
}
