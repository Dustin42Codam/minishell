#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "environ.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void	free_command_argv(t_command *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		cmd->argv[i] = NULL;
		i++;
	}
	free(cmd->argv);
	cmd = NULL;
}

void	make_command_argv(t_data *data, t_astree *node, t_command *cmd)
{
	t_astree	*tmp;

	cmd->argc = 0;
	tmp = node;
	while (tmp && tmp->type & (AST_WORD))
	{
		cmd->argc++;
		tmp = tmp->right;
	}
	cmd->argv = (char **)secure_calloc(cmd->argc + 1, sizeof(char *));
	cmd->argc = 0;
	tmp = node;
	while (tmp && tmp->type & (AST_WORD))
	{
		if (cmd->argc == 0)
			cmd->builtin_id = search_command(tmp, data->env);
		cmd->argv[cmd->argc] = ft_strdup(tmp->str);
		if (cmd->argv[cmd->argc] == NULL)
			exit_shell(errno);
		cmd->argc++;
		tmp = tmp->right;
	}
	cmd->env = data->env;
}

int	execute_command_argv(t_command *cmd, t_environ *env)
{
	pid_t	pid;
	int		statloc;
	char	**env_array;

	env_array = environ_get_array(env);
	pid = fork();
	if (pid == -1)
		exit_shell(errno);
	else if (pid == 0)
	{
		if (execve(cmd->argv[0], cmd->argv, env_array) == -1)
			exit_shell(errno);
	}
	else
	{
		wait(&statloc);
	}
	free_command_argv(cmd);
	return (0);
}
