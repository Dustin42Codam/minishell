/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redirection_util.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts <alkrust@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 15:26:08 by alkrusts      #+#    #+#                 */
/*   Updated: 2021/10/28 15:29:54 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include "lexer.h"
#include <stdlib.h>

void	del_parent(t_exec *stru, t_astree *node)
{
	stru->parent = node->parent;
	if (node->parent)
	{
		node->right = node->parent->right;
		node->parent = node->parent->parent;
	}
	if (node->parent)
	{
		if (node->parent->right == stru->parent)
			node->parent->right = node;
		else
			node->parent->left = node;
	}
	if (stru->parent)
	{
		free(stru->parent->str);
		stru->parent->str = NULL;
		free(stru->parent);
		stru->parent = NULL;
	}
	if (node->right)
		node->right->parent = node;
	stru->root = node;
}
