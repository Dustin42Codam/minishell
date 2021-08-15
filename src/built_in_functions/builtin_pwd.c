#include "minishell.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int	builtin_pwd(t_command *cmd)
{
	char	*cwd;

	errno = 0;
	if (cmd->argc > 1 && cmd->argv[1][0] == '-')
	{
		minishell_putendl_fd("minishell: pwd: options are not supported", 2);
		return (2);
	}
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
		return (errno);
	minishell_putendl_fd(cwd, cmd->fd.write);
	free(cwd);
	return (0);
}
