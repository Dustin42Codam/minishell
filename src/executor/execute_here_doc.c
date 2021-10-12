#include "minishell.h"
#include "environ.h"
#include "libft.h"
#include "lexer.h"
#include "executor.h"
#include "expansion.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

static void	expand_input(t_data *data, char *line, int pipe_write)
{
	t_token	*tmp;

	tmp = minishell_calloc(1, sizeof(t_token));
	tmp->str = line;
	tmp->type |= EXPAND;
	expand_variables(tmp, data->env);
	minishell_write(pipe_write, tmp->str, ft_strlen(tmp->str));
	minishell_write(pipe_write, "\n", 1);
	free(tmp);
}

static void	setup_pipe(t_file_io *fd)
{
	if (pipe(fd->pipe) == -1)
		exit_minishell(errno);
	fd->dup_stdin = 1;
	fd->dup_stdout = 0;
	fd->read = fd->pipe[0];
	if (fd->output == 0)
		fd->write = STDOUT_FILENO;
}

static void	read_input(t_data *data, t_astree *node, t_file_io fd)
{
	char	*input;
	char	*delimeter;

	input = NULL;
	delimeter = node->str;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			continue ;
		if (errno)
			exit_minishell(errno);
		else if (environ_compare(input, delimeter) == 1)
			break ;
		if (!(node->type & RMQUOTE) && ft_strchr(input, '$'))
			expand_input(data, input, fd.pipe[1]);
		else
		{
			minishell_write(fd.pipe[1], input, ft_strlen(input));
			minishell_write(fd.pipe[1], "\n", 1);
		}
	}
}

void	execute_here_doc(t_data *data, t_astree *node, t_file_io fd)
{
	setup_pipe(&fd);
	read_input(data, node, fd);
	close(fd.pipe[1]);
	if (fd.input)
	{
		close(fd.input);
		fd.input = 0;
	}
	execute_command(data, node->right, fd);
	close(fd.pipe[0]);
}
