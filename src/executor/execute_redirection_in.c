/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redirection_in.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 23:19:23 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/09 03:46:15 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

void	execute_redirection_in(t_data *data, t_astree *node, t_file_io *fd)
{
	t_astree	*root;
	t_astree	*parent;

	root = node;
	while (node && node->type & (AST_REDIR_IN | AST_HERE_DOC))
	{
		if (fd->input)
		{
			close(fd->input);
			parent = node->parent;
			node->right = node->parent->right;
			node->parent = node->parent->parent;
			free(parent->str);
			free(parent);
			if (node->right)
				node->right->parent = node;
			root = node;
			data->astree = root;
		}
		if (node->type & AST_REDIR_IN)
			fd->input = open(node->str, O_RDONLY);
		else if (node->type & AST_HERE_DOC)
			fd->input = 0;
		if (fd->input == -1)
			return (print_error(data, node->str, errno));
		node = node->left;
	}
	if (root->left && root->left->type & AST_REDIR_OUT)
		execute_redirection_out(data, root->left, fd);
	if (root && root->type & AST_REDIR_OUT)
		execute_redirection_out(data, root, fd);
	if (root && root->type & AST_HERE_DOC)
		execute_here_doc(data, root, *fd);
	if (root->right && data->error == 0)
		execute_word_list(data, root->right, *fd);
}
