#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <string.h>
#include <errno.h>
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
		fd.input = open(node->str, O_RDONLY);
		if (fd.input == -1)
			return (print_error(data, node->str, errno));
		if (node->right)
			execute_word_list(data, node->right, fd);
	}
	else if (node->type & (AST_REDIR_OUT | AST_APPEND))
	{
		if (node->type & AST_REDIR_OUT)
			fd.output = open(node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (node->type & AST_APPEND)
			fd.output = open(node->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd.output == -1)
			return (print_error(data, node->str, errno));
		fd.write = fd.output;
		if (node->right)
			execute_word_list(data, node->right, fd);
	}
	else if (node->type == AST_WORD)
		execute_word_list(data, node, fd);
}
