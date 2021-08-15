#include "minishell.h"
#include "environ.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static int	builtin_cd_error(char *path, int error_id)
{
	minishell_putstr_fd("minishell: cd: ", 2);
	minishell_putstr_fd(path, 2);
	minishell_putstr_fd(": ", 2);
	minishell_putendl_fd(strerror(error_id), 2);
	return (error_id);
}

int	builtin_cd(t_command *cmd, t_environ *env)
{
	char	*cwd;

	errno = 0;
	if (cmd->argc != 2)
	{
		minishell_putendl_fd("minishell: cd: single argument required", 2);
		return (1);
	}
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
		return (errno);
	environ_set(env, "OLDPWD", cwd);
	free(cwd);
	chdir(cmd->argv[1]);
	if (errno)
		return (builtin_cd_error(cmd->argv[1], errno));
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
		return (errno);
	environ_set(env, "PWD", cwd);
	free(cwd);
	return (0);
}
