#include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int	builtin_pwd(t_command *cmd)
{
	char	*cwd;

	errno = 0;
	if (cmd->argc > 1)
	{
		ft_putendl_fd("pwd: invalid option", 2);
		return (ECANCELED);
	}
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
		return (errno);
	ft_putendl_fd(cwd, 1);
	if (errno)
		return (errno);
	free(cwd);
	return (0);
}
