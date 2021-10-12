#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "libft.h"
#include "lexer.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>

static bool	is_empty(char *line)
{
	size_t	i;
	char	c;

	i = 0;
	if (line == NULL)
		return (true);
	while (line[i])
	{
		c = line[i];
		if (c != '\t' && c != '\n' && c != '\v' && \
			c != '\f' && c != '\r' && c != ' ')
			return (false);
		i++;
	}
	return (true);
}

static void	pipe_to_stdin(t_data *data, t_file_io fd)
{
	free(data->line);
	data->line = NULL;
	while (!data->line || !data->line[0] || is_empty(data->line))
		data->line = readline("> ");
	data->line_len = ft_strlen(data->line);
	free_token_list(data->token);
	data->token_mask = 0;
	lexer(&data, data->line);
	delete_ast(data->astree);
	parser(data);
	dup2(fd.pipe[0], STDIN_FILENO);
	execute(data);
}

static void	setup_next_pipe(t_file_io *fd)
{
	close(fd->write);
	fd->read = fd->pipe[0];
	if (pipe(fd->pipe) == -1)
		exit_minishell(errno);
	fd->write = fd->pipe[1];
	fd->dup_stdout = 1;
	fd->dup_stdin = 1;
}

static void	setup_pipe_end(t_file_io *fd)
{
	close(fd->write);
	fd->read = fd->pipe[0];
	fd->dup_stdin = 1;
	fd->dup_stdout = 0;
}

void	execute_pipeline(t_data *data, t_file_io fd)
{
	t_astree	*node;

	if (pipe(fd.pipe) == -1)
		exit_minishell(errno);
	fd.dup_stdin = 0;
	fd.dup_stdout = 1;
	fd.read = fd.pipe[0];
	fd.write = fd.pipe[1];
	fd.output = 0;
	execute_command(data, data->astree->left, fd);
	node = data->astree->right;
	while (node && node->type == AST_PIPE)
	{
		setup_next_pipe(&fd);
		execute_command(data, node->left, fd);
		close(fd.read);
		node = node->right;
	}
	setup_pipe_end(&fd);
	if (node == NULL)
		pipe_to_stdin(data, fd);
	else
		execute_command(data, node, fd);
	close(fd.pipe[0]);
}
