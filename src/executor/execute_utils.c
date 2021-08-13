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
	cmd = NULL;// add env free
}

static void	init_cmd(t_data *data, t_command *cmd, t_file_io fd)
{
	cmd->env = data->env;
	cmd->last_exit_code = data->exit_status;
	cmd->fd = fd;
}

void	make_command_argv(t_data *data, t_astree *node, t_command *cmd, t_file_io fd)
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

static void	execute_child(t_command	*cmd, char **env_array)
{
	// printf("Executing command '%s'\tPID:\t[%d]\n", cmd->argv[0], getpid());
	if (cmd->fd.dup_stdin)
		dup2(cmd->fd.read, STDIN_FILENO);
	if (cmd->fd.dup_stdout)
		dup2(cmd->fd.write, STDOUT_FILENO);
	if (cmd->fd.redirect_out)
		dup2(cmd->fd.redirect_out, STDOUT_FILENO);
	if (cmd->fd.redirect_in)
		dup2(cmd->fd.redirect_in, STDIN_FILENO);
	if (errno || execve(cmd->argv[0], cmd->argv, env_array) == -1)
	{
		dup2(cmd->fd.save_stdout, 1);
		printf("minishell: %s - Error: %s [%d]\n", 
			cmd->argv[0], strerror(errno), errno);
		exit(errno);
	}
}

int	execute_command_argv(t_command *cmd, t_environ *env)
{
	pid_t	pid;
	int		stat;
	char	**env_array;	//free later

	env_array = environ_get_array(env);
	pid = fork();
	if (pid == -1)
		exit_minishell(errno);
	else if (pid == 0)
		execute_child(cmd, env_array);
	waitpid(pid, &stat, 0);
	free_command_argv(cmd);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	return (0);
}
