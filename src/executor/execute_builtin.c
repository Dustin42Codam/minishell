#include "minishell.h"
#include "builtins.h"

static int	is_end_of_pipe(t_command *cmd)
{
	return (cmd->fd.dup_stdin == 1 && cmd->fd.dup_stdout == 0);
}

int	execute_builtin(t_command *cmd, t_environ *env)
{
	if (is_end_of_pipe(cmd))
		cmd->fd.write = cmd->fd.save_stdout;
	if (cmd->builtin_id == ECHO)
		return (builtin_echo(cmd));
	else if (cmd->builtin_id == CD)
		return (builtin_cd(cmd, env));
	else if (cmd->builtin_id == PWD)
		return (builtin_pwd(cmd));
	else if (cmd->builtin_id == EXPORT)
		return (builtin_export(cmd, env));
	else if (cmd->builtin_id == UNSET)
		return (builtin_unset(cmd, env));
	else if (cmd->builtin_id == ENV)
		return (builtin_env(cmd, env));
	else if (cmd->builtin_id == EXIT)
		return (builtin_exit(cmd));
	return (0);
}
