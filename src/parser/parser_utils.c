/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:56:50 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:57:47 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include <stdlib.h>

void	init_ast_node(t_astree *node, char *arg, int type)
{
	node->type = type;
	if (arg)
	{
		node->str = arg;
		node->type |= AST_WORD;
	}
}

void	insert_ast_node(t_astree *node, t_astree *left, t_astree *right)
{
	node->left = left;
	node->right = right;
}

void	delete_ast(t_astree *node)
{
	if (node == NULL)
		return ;
	if (node->str)
		free(node->str);
	delete_ast(node->right);
	delete_ast(node->left);
	free(node);
	node = NULL;
}

int	get_ast_node_type(int type)
{
	if (type == PIPE)
		return (AST_PIPE);
	else if (type == HERE_DOC)
		return (AST_HERE_DOC);
	else if (type == REDIR_IN)
		return (AST_REDIR_IN);
	else if (type == APPEND)
		return (AST_APPEND);
	else if (type == REDIR_OUT)
		return (AST_REDIR_OUT);
	else
		return (AST_WORD);
}
