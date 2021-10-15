/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipeline.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:29 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/14 17:43:39 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "libft.h"
#include "lexer.h"
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>

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
	execute_command(data, node, fd);
	close(fd.pipe[0]);
}
