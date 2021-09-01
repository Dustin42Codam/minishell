#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "environ.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

static void	free_command_argv(t_command *cmd, char **env_array)
{
	size_t	i;

	i = 0;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

static void	init_cmd(t_data *data, t_command *cmd, t_file_io fd)
{
	cmd->exit_status = data->exit_status;
	cmd->fd = fd;
	cmd->env = data->env;
}

void	make_command(t_data *data, t_astree *node, t_command *cmd, t_file_io fd)
{
	t_astree	*tmp;

	cmd->argc = 0;
	tmp = node;
	while (tmp && tmp->type & (AST_WORD))
	{
		cmd->argc++;
		tmp = tmp->right;
	}
	cmd->argv = (char **)minishell_calloc(cmd->argc + 1, sizeof(char *));
	cmd->argc = 0;
	tmp = node;
	while (tmp && tmp->type & (AST_WORD))
	{
		if (cmd->argc == 0)
			cmd->builtin_id = search_command(tmp, data->env);
		cmd->argv[cmd->argc] = ft_strdup(tmp->str);
		if (cmd->argv[cmd->argc] == NULL)
			exit_minishell(errno);
		cmd->argc++;
		tmp = tmp->right;
	}
	init_cmd(data, cmd, fd);
}

/**
 * a little workaround for the fork() - errno - macOS bug:
 * - macOS sets errno = 22 after fork() so we need to set errno to 0 manually
 * - a call to isatty() guarantees that we don't reset
 * 		the termios structure on a pipe/fifo file object
 * - if isatty() fails it sets errno to ENOTTY
 * 		(fd is not a terminal, we are in a pipe)
 * 		so we need to set errno again back to 0
 * - then we can use errno again inside short if statements.
 * 		The first error that gets detected will be used as exit code.
**/
static void	execute_child(t_command *cmd, char **env_array)
{
	errno = 0;
	if (errno == 0 && cmd->fd.dup_stdin)
		dup2(cmd->fd.read, STDIN_FILENO);
	if (errno == 0 && cmd->fd.dup_stdout)
		dup2(cmd->fd.write, STDOUT_FILENO);
	if (errno == 0 && cmd->fd.output)
		dup2(cmd->fd.output, STDOUT_FILENO);
	if (errno == 0 && cmd->fd.input)
		dup2(cmd->fd.input, STDIN_FILENO);
	if (errno || execve(cmd->argv[0], cmd->argv, env_array) == -1)
	{
		dup2(cmd->fd.save_stdout, STDOUT_FILENO);
		printf("minishell: %s - Error: %s [%d]\n",
			cmd->argv[0], strerror(errno), errno);
		exit(errno);
	}
}

void	execute_command_argv(t_data *data, t_command *cmd, t_environ *env)
{
	pid_t	pid;
	int		stat;
	char	**env_array;

	env_array = environ_get_array(env);
	incrment_global_sig();
	pid = fork();
	if (pid == -1)
		exit_minishell(errno);
	else if (pid == 0)
		execute_child(cmd, env_array);
	errno = 0;
	waitpid(pid, &stat, 0);
	decrement_global_sig();
	free_command_argv(cmd, env_array);
	if (WIFEXITED(stat))
		data->exit_status = WEXITSTATUS(stat);
}
