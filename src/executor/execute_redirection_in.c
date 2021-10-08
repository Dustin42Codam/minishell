/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redirection_in.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/08 23:19:23 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/08 23:29:20 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <errno.h>
#include <fcntl.h>

void	execute_redirection_in(t_data *data, t_astree *node, t_file_io *fd)
{
	t_astree	*root;

	root = node;
	while (node && node->type & (AST_REDIR_IN | AST_HERE_DOC))
	{
		if (fd->input)
		{
			close(fd->input);	// add: delete redundant AST nodes
			
		}
		fd->input = open(node->str, O_RDONLY);
		if (fd->input == -1)
			return (print_error(data, node->str, errno));
		node = node->left;
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
