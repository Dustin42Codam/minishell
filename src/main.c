#include "minishell.h"
#include "get_next_line.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

static void	print_prompt(void)
{
	// ft_putstr_fd(BCYAN, 1);
	ft_putstr_fd("minishell> ", 1);
	// ft_putstr_fd(RESET, 1);
	if (errno)
		exit_shell(errno);
}

int	main(void)
{
	char	*line;
	int		ret;

	ret = 1;
	while (1)
	{
		print_prompt();
		// line = read_line();
		get_next_line(0, &line);
		printf("[%s]\n", line);
		free(line);
		line = 0;
	}
	return (0);
}
