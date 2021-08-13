#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

void	print_error(t_data *data, char *str, int error_id)
{
	printf("minishell: %s: %s\n", str, strerror(error_id));
	data->exit_status = errno;
	errno = 0;
}

void	execute_command(t_data *data, t_astree *node, t_file_io fd)
{
	if (node == NULL)
		return ;
	else if (node->type & AST_REDIR_IN)
	{
		fd.redirect_in = open(node->str, O_RDONLY);
		if (fd.redirect_in == -1)
			return (print_error(data, node->str, errno));
		if (node->right)
			execute_word_list(data, node->right, fd);
	}
	else if (node->type & (AST_REDIR_OUT | AST_APPEND))
	{
		if (node->type & AST_REDIR_OUT)
			fd.redirect_out = open(node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (node->type & AST_APPEND)
			fd.redirect_out = open(node->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd.redirect_out == -1)
			return (print_error(data, node->str, errno));
		fd.write = fd.redirect_out;
		if (node->right)
			execute_word_list(data, node->right, fd);
	}
	else if (node->type == AST_WORD)
		execute_word_list(data, node, fd);
}
