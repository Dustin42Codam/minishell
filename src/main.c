#include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

static void	print_prompt(void)
{
	ft_putstr_fd(BCYAN, 1);
	ft_putstr_fd("minishell> ", 1);
	ft_putstr_fd(RESET, 1);
	if (errno)
		exit_shell(errno);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		print_prompt();
		line = read_line();
		free(line);
		line = 0;
	}
	return (0);
}
