/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_here_doc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:27 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/31 04:35:08 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "expansion.h"
#include <errno.h>
#include <signal.h>
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
	if (pipe(fd->here_doc) == -1)
		exit_minishell(errno);
	fd->dup_stdin = 1;
	fd->read = fd->here_doc[0];
	if (fd->output == 0 && fd->pipe[1] == 0)
		fd->write = STDOUT_FILENO;
}

static void	init_signal_handler(void)
{
	if (signal(SIGINT, sig_herdocs) == SIG_ERR
		|| signal(SIGQUIT, sig_herdocs) == SIG_ERR)
		exit_minishell_custom("ERROR SIGINT ");
}

static void	read_input(t_data *data, t_astree *node, t_file_io *fd)
{
	char	*input;
	char	*delimeter;

	input = NULL;
	delimeter = node->str;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (errno)
			exit_minishell(errno);
		else if (input == NULL || environ_compare(input, delimeter) == 1)
			break ;
		if (!(node->type & RMQUOTE) && ft_strchr(input, '$'))
			expand_input(data, input, fd->here_doc[1]);
		else
		{
			minishell_write(fd->here_doc[1], input, ft_strlen(input));
			minishell_write(fd->here_doc[1], "\n", 1);
		}
		free(input);
		input = NULL;
	}
	free(input);
}

t_astree	*execute_here_doc(t_data *data, t_astree *node,
		t_file_io *fd, t_exec *stru)
{
	setup_pipe(fd);
	g_sig = 0;
	init_signal_handler();
	read_input(data, node, fd);
	while (node->left && node->left->type & AST_HERE_DOC)
	{
		node = node->left;
		delete_parent(stru, &node);
		read_input(data, node, fd);
	}
	close(fd->here_doc[1]);
	fd->here_doc[1] = 0;
	if (fd->input)
	{
		close(fd->input);
		fd->input = 0;
	}
	return (node);
}
