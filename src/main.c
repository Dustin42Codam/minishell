#include "minishell.h"
#include "get_next_line.h"
#include "libft.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static void	print_prompt(void)
{
	char	*cwd;

	cwd = getcwd(0, PATH_MAX);
	if (cwd)
	{
		ft_putstr(BGRN);
		ft_putstr("@minishell");
		ft_putstr(WHT);
		ft_putchar(':');
		ft_putstr(BBLU);
		ft_putstr(cwd);
		ft_putstr(WHT);
		ft_putstr("$ ");
		ft_putstr(END);
		free(cwd);
	}
	if (errno)
		exit_shell(errno);
}

int	main(void)
{
	char	*line;
	t_built_in	*built_in;

	built_in = init();
	while (1)
	{
		print_prompt();
		get_next_line(0, &line);
		if (errno)
			exit_shell(errno);
		if (!call(line))
			exit(1);
		free(line);
		line = NULL;
	}
	return (0);
}
