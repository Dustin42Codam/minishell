#include "minishell.h"
#include "builtins.h"

int	execute_builtin(t_command *cmd, t_environ *env)
{
	if (cmd->builtin_id == ECHO)
		return (builtin_echo(cmd));
	else if (cmd->builtin_id == ENV)
		return (builtin_env(cmd, env));
	else if (cmd->builtin_id == PWD)
		return (builtin_pwd(cmd, env));
	return (0);
}
