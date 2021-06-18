#include "minishell.h"
#include <stdio.h>

void	print_token_types(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("[%s],\ttype:%d\t", tmp->str, tmp->type);
		if (tmp->type == EMPTY)
			printf(" EMPTY");
		if (tmp->type & WORD)
			printf(" WORD");
		if (tmp->type & SEMICOLON)
			printf(" SEMICOLON");
		if (tmp->type & PIPE)
			printf(" PIPE");
		if (tmp->type & REDIR_IN)
			printf(" REDIR_IN");
		if (tmp->type & REDIR_OUT)
			printf(" REDIR_OUT");
		if (tmp->type & APPEND)
			printf(" APPEND");
		if (tmp->type & EXPAND)
			printf(" EXPAND");
		if (tmp->type & SQUOTE)
			printf(" SQUOTE");
		if (tmp->type & DQUOTE)
			printf(" DQUOTE");
		tmp = tmp->next;
		printf("\n");
	}
}
