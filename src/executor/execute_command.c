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
	errno = 0;
}

static void	execute_redirection_in(t_data *data, t_astree *node, t_file_io fd)
{
	fd.input = open(node->str, O_RDONLY);
	if (fd.input == -1)
		return (print_error(data, node->str, errno));
	if (node->right)
		execute_word_list(data, node->right, fd);
}

static void	execute_redirection_out(t_data *data, t_astree *node, t_file_io fd)
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

void	execute_command(t_data *data, t_astree *node, t_file_io fd)
{
	if (node == NULL)
		return ;
	else if (node->type & AST_REDIR_IN)
		execute_redirection_in(data, node, fd);
	else if (node->type & (AST_REDIR_OUT | AST_APPEND))
		execute_redirection_out(data, node, fd);
	else if (node->type & AST_HERE_DOC)
		execute_here_doc(data, node, fd);
	else if (node->type == AST_WORD)
		execute_word_list(data, node, fd);
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
