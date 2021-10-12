/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variables.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:56:13 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:57:56 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "expansion.h"
#include <stdlib.h>

static t_token	*delete_token(t_token *token, t_token *token_to_delete)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != token_to_delete)
	{
		if (token_to_delete == tmp)
		{
			free(token_to_delete->str);
			free(token_to_delete);
			return (tmp);
		}
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
**/

void	expand_variables(t_token *token, t_environ *env)
{
	t_token		*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type & HERE_DOC && tmp->next)
			tmp = tmp->next;
		else
		{
			while (tmp->type & EXPAND)
			{
				do_variable_expansion(tmp, env);
				if (check_expansion(tmp))
					continue ;
				if (tmp->type == WORD)
					split_words(tmp);
				if (tmp->type == WORD && tmp->str[0] == 0)
				{
					tmp = delete_token(token, tmp);
					continue ;
				}
			}
		}
		tmp = tmp->next;
	}
}
