#include "minishell.h"

#include <unistd.h>
#include <errno.h>

int	ft_putchar_ret_int(int c)
{
	const int	WRITE_FAILED = -1;

	if (write(1, &c, 1) == WRITE_FAILED)
		exit_minishell(errno);
	return (1);
}
