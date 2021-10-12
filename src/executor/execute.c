#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "executor.h"
#include <errno.h>

static void	setup_fd(t_file_io *fd)
{
	ft_memset(fd, 0, sizeof(t_file_io));
	fd->read = STDIN_FILENO;
	fd->write = STDOUT_FILENO;
	fd->save_stdin = dup(STDIN_FILENO);
	fd->save_stdout = dup(STDOUT_FILENO);
	if (errno)
		exit_minishell(errno);
}

static void	restore_fd(t_file_io *fd)
{
	dup2(fd->save_stdin, STDIN_FILENO);
	dup2(fd->save_stdout, STDOUT_FILENO);
	close(fd->save_stdin);
	close(fd->save_stdout);
	if (fd->output)
		close(fd->output);
	if (errno)
		exit_minishell(errno);
}

void	execute(t_data *data)
{
	t_file_io	fd;

	if (data->astree == NULL)
		return ;
	setup_fd(&fd);
	if (data->token_mask & PIPE)
		execute_pipeline(data, fd);
	else
		execute_command(data, data->astree, fd);
	restore_fd(&fd);
}
