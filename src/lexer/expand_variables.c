#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "expansion.h"
#include <stdlib.h>

static t_token	*delete_token(t_data *data, t_token *token_to_delete)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp->next != token_to_delete)
	{
		if (token_to_delete == tmp)
			return (tmp);
		tmp = tmp->next;
	}
	tmp->next = token_to_delete->next;
	if (tmp->end == token_to_delete->start - 1)
		tmp->end = token_to_delete->end;
	free(token_to_delete->str);
	free(token_to_delete);
	return (tmp->next);
}

/**
 * expand_variables - expands environment variables within token strings
 *	- iterates through list of tokens
 *	- does variable expansion on tokens marked with EXPAND
 *	TODO:
 *	- pass t_data struct with the copy of environment to do expansions
**/
void	expand_variables(t_data *data)
{
	t_token		*tmp;

	tmp = data->token;
	while (tmp)
	{
		while (tmp->type & EXPAND)
		{
			do_variable_expansion(tmp, data->env);
			if (check_expansion(tmp))
				continue ;
			if (tmp->type == WORD)
				split_words(tmp);
			if (tmp->type == WORD && tmp->str[0] == 0)
			{
				tmp = delete_token(data, tmp);
				continue ;
			}
		}
		tmp = tmp->next;
	}
}
