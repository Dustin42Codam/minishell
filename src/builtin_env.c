#include "minishell.h"
#include <errno.h>

int	builtin_env(t_command *cmd, t_environ *env)
{
	errno = 0;
	if (cmd->argc > 1)
	{
		ft_putendl_fd("env: invalid option", 2);
		return (ECANCELED);
	}
	while (env && errno == 0)
	{
		ft_putendl_fd(env->key_value, 1);
		env = env->next;
	}
	return (errno);
}
