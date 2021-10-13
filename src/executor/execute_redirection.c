/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redirection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/09 04:16:44 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/12 07:17:34 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "lexer.h"
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

void	execute_redirection(t_data *data, t_astree *node, t_file_io *fd)
{
	t_astree	*root;
	t_astree	*parent;

	root = node;
	while (node && is_redirection(node->type))
	{
		if (node->type & AST_REDIR_IN)
		{
			if (fd->input)
			{
				close(fd->input);
				parent = node->parent;
				node->right = node->parent->right;
				node->parent = node->parent->parent;
				if (node->parent)
				{
					node->parent->left = node;
				}
				if (parent)
				{
					free(parent->str);
					free(parent);
					parent = NULL;
				}
				if (node->right)
					node->right->parent = node;
				root = node;
			}
			if (node->type & AST_REDIR_IN)
				fd->input = open(node->str, O_RDONLY);
			else if (node->type & AST_HERE_DOC)
				fd->input = 0;
			if (fd->input == -1)
			{
				print_error(data, node->str, errno);
				while (node->parent)
					node = node->parent;
				data->astree = node;
				return ;
			}
		}
		else if (node->type & (AST_REDIR_OUT | AST_APPEND))
		{
			if (fd->output)
			{
				close(fd->output);
				parent = node->parent;
				if (node->parent)
					node->right = node->parent->right;
				if (node->parent)
					node->parent = node->parent->parent;
				if (node->parent)
				{
					node->parent->left = node;
					free(parent->str);
					free(parent);
					parent = NULL;
				}
				if (node->right)
					node->right->parent = node;
				root = node;
			}
			if (node->type & AST_REDIR_OUT)
				fd->output = open(node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else if (node->type & AST_APPEND)
				fd->output = open(node->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd->output == -1)
				return (print_error(data, node->str, errno));
			fd->write = fd->output;
		}
		if (node->left)
			node = node->left;
		else if (node->right)
			node = node->right;
		else
			break ;
	}
	if (node && node->type & AST_HERE_DOC)
	{
		node->right = root->right;
		execute_here_doc(data, node, *fd);
		node->right = NULL;
		return ;
	}
	if ((data->token_mask & PIPE) == 0)
	{
		while (node->parent)
			node = node->parent;
	}
	if ((data->token_mask & PIPE) == 0)
		data->astree = node;
	if (data->astree->right && data->astree->right->type & AST_WORD && (data->token_mask & PIPE) == 0)
		execute_word_list(data, data->astree->right, *fd);
	else if (node && node->type == AST_WORD)
		execute_word_list(data, node, *fd);
}
