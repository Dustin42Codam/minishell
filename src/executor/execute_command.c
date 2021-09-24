#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

void	print_error(t_data *data, char *str, int error_id)
{
	printf("minishell: %s: %s\n", str, strerror(error_id));
	data->exit_status = errno;
	data->error = errno;
	errno = 0;
}

// static void	execute_redirection_out(t_data *data, t_astree *node, t_file_io fd)
// {
	// if (node->type & AST_REDIR_OUT)
		// fd.output = open(node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// else if (node->type & AST_APPEND)
		// fd.output = open(node->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	// if (fd.output == -1)
		// return (print_error(data, node->str, errno));
	// fd.write = fd.output;
	// if (node->right)
		// execute_word_list(data, node->right, fd);
// }

static void	execute_redirection_out(t_data *data, t_astree *node, t_file_io *fd)
{
	t_astree	*tmp;

	tmp = node;
	while (tmp && tmp->type & (AST_REDIR_OUT | AST_APPEND))
	{
		if (fd->output)
			close(fd->output);
		if (tmp->type & AST_REDIR_OUT)
			fd->output = open(tmp->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (tmp->type & AST_APPEND)
			fd->output = open(tmp->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd->output == -1)
			return (print_error(data, tmp->str, errno));
		tmp = tmp->left;
	}
	fd->write = fd->output;
	if (node->left && node->left->type & AST_REDIR_IN)
		execute_redirection_in(data, node->left, fd);
	if (tmp && tmp->type & AST_HERE_DOC)
	{
		tmp = node->right;
		node = node->left;
		node->right = tmp;
		execute_here_doc(data, node, *fd);
	}
	if (node->right && data->error == 0)
		execute_word_list(data, node->right, *fd);
}

void	execute_redirection_in(t_data *data, t_astree *node, t_file_io *fd)
{
	t_astree	*tmp;

	tmp = node;
	while (tmp && tmp->type & AST_REDIR_IN)
	{
		if (fd->input)
			close(fd->input);
		fd->input = open(tmp->str, O_RDONLY);
		if (fd->input == -1)
			return (print_error(data, tmp->str, errno));
		tmp = tmp->left;
	}
	if (node->left && node->left->type & AST_REDIR_OUT)
		execute_redirection_out(data, node->left, fd);
	if (tmp && tmp->type & AST_REDIR_OUT)
		execute_redirection_out(data, tmp, fd);
	if (tmp && tmp->type & AST_HERE_DOC)
		execute_here_doc(data, tmp, *fd);
	if (node->right && data->error == 0)
		execute_word_list(data, node->right, *fd);
}

void	execute_command(t_data *data, t_astree *node, t_file_io fd)
{
	if (node == NULL)
		return ;
	else if (node->type & AST_REDIR_IN)
		execute_redirection_in(data, node, &fd);
	else if (node->type & (AST_REDIR_OUT | AST_APPEND))
		execute_redirection_out(data, node, &fd);
	else if (node->type & AST_HERE_DOC)
		execute_here_doc(data, node, fd);
	else if (node->type == AST_WORD)
		execute_word_list(data, node, fd);
	data->error = 0;
}
