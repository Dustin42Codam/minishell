/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redirection_out.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 23:22:42 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/09 00:17:02 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

void	execute_redirection_out(t_data *data, t_astree *node, t_file_io *fd)
{
	t_astree	*root;
	t_astree	*parent;

	root = node;
	while (node && node->type & (AST_REDIR_OUT | AST_APPEND))
	{
		if (fd->output)
		{
			close(fd->output);
			parent = node->parent;
			node->right = node->parent->right;
			node->parent = node->parent->parent;
			free(parent->str);
			free(parent);
			node->right->parent = node;
			root = node;
			data->astree = root;
		}
		if (node->type & AST_REDIR_OUT)
			fd->output = open(node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (node->type & AST_APPEND)
			fd->output = open(node->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd->output == -1)
			return (print_error(data, node->str, errno));
		node = node->left;
	}
	fd->write = fd->output;
	if (root->left && root->left->type & AST_REDIR_IN)
		execute_redirection_in(data, root->left, fd);
	if (root && root->type & AST_HERE_DOC)
	{
		root = node->right;
		node = node->left;
		node->right = root;
		execute_here_doc(data, node, *fd);
	}
	if (root->right && data->error == 0)
		execute_word_list(data, root->right, *fd);
}
