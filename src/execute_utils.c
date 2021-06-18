#include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void free_command_argv(t_command *cmd)
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

void make_command_argv(t_astree *node, t_command *cmd)
{
	t_astree	*tmp;

	cmd->argc = 0;
	tmp = node;
	while (tmp && tmp->type & (AST_CMD_ARG | AST_CMD))
	{
		cmd->argc++;
		tmp = tmp->right;
	}
	cmd->argv = (char **)ft_calloc(cmd->argc + 1, sizeof(char*));
	if (errno)
		exit_shell(errno);

	cmd->argc = 0;
	tmp = node;
	while (tmp && tmp->type & (AST_CMD_ARG | AST_CMD))
	{
		cmd->argv[cmd->argc] = ft_strdup(tmp->str);
		if (errno)
			exit_shell(errno);
		cmd->argc++;
		tmp = tmp->right;
	}
}

void	execute_command_argv(t_command *cmd, char **env)
{
	pid_t	pid;
	int		statloc;

	pid = fork();
	if (errno)
		exit_shell(errno);
	else if (pid == 0)
	{
		if (execve(cmd->argv[0], cmd->argv, env) == -1)
			exit_shell(errno);
	}
	else
	{
		wait(&statloc);
	}
	free_command_argv(cmd);
}
