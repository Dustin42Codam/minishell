#include "minishell.h"
#include <errno.h>

int	builtin_env(t_command *cmd, t_environ *env)
{
	errno = 0;
	if (cmd->argc > 1)
	{
		minishell_putendl_fd("minishell: env: arguments are not supported", 2);
		return (ECANCELED);
	}
	while (env && errno == 0)
	{
		minishell_putendl_fd(env->key_value, cmd->fd.write);
		env = env->next;
	}
	return (errno);
}
