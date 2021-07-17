#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "expansion.h"
#include <errno.h>
#include <stdlib.h>

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
			do_variable_expansion(tmp);
			if (check_expansion(tmp))
				continue ;
			if (tmp->type & ~(SQUOTE | DQUOTE))
				split_words(tmp);
		}
		tmp = tmp->next;
	}
	(void)data;
}
