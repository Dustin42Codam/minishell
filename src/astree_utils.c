#include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

void	init_ast_node(t_astree *node, char *arg, int type)
{
	node->type = type;
	if (arg)
	{
		node->str = arg;
		node->type |= AST_TOKEN;
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
