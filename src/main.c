#include "minishell.h"
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

int	main(int argc, char *argv[], char **envp)
{
	t_data	*data;

	data = init_data(envp);
	while (1)
	{
		print_prompt();
		data->line_len = read_line(&data->line);
		free(data->line);
		data->line = NULL;
	}
	free_data(data);
	(void)argc;
	(void)argv;
	return (0);
}
