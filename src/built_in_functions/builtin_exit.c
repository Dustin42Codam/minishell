#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

static int	validate_argument(char *arg)
{
	size_t	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (arg[i] == '\0')
		return (EXIT_FAILURE);
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_command *cmd)
{
	int	exit_code;

	if (cmd->argc == 1)
		exit(cmd->exit_status);
	if (cmd->argc > 1 && validate_argument(cmd->argv[1]))
	{
		minishell_putendl_fd("minishell: exit: \
			only one numeric argument allowed", 2);
		return (1);
	}
	exit_code = ft_atoi(cmd->argv[1]);
	exit((unsigned char)exit_code);
}
