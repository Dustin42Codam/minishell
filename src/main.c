#include "minishell.h"
#include "get_next_line.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

static void	print_prompt(void)
{
	char	*cwd;

	cwd = getcwd(0, PATH_MAX);
	if (cwd)
	{
		ft_putstr(BGRN);
		ft_putstr_fd("@minishell", 1);
		ft_putstr(WHT);
		ft_putchar(':');
		ft_putstr(BBLU);
		ft_putstr_fd(cwd, 1);
		ft_putstr(WHT);
		ft_putstr_fd("$ ", 1);
		free(cwd);
	}
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
		get_next_line(0, &line);
		free(line);
		line = 0;
	}
	return (0);
}
