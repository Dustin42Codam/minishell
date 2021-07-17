#include "minishell.h"
#include "lexer.h"
#include "libft.h"

/**
 * make_token_meta() - creates tokens for meta characters (<>|)
 * -	gets the correct type of token  
 * -	copies meta char into token string  
 * -	if append ">>" or here doc "<<" then it copies
 * 		both characters into token string
 * -	creates next empty token only if the next char is not a meta char.
 * 		This is needed in order to prevent double mallocs.
**/
void	make_token_meta(t_token **token, t_data **data, size_t *i, size_t *j)
{
	int		token_type;

	token_type = get_token_type((*data)->line + (*i));
	if (token_type & (HERE_DOC | APPEND))
	{
		(*token)->str[(*j)] = (*data)->line[(*i)];
		(*i)++;
		(*j)++;
	}
	(*token)->str[(*j)] = (*data)->line[(*i)];
	(*token)->type |= token_type;
	if (is_meta((*data)->line[(*i) + 1]) == FALSE)
		init_new_token(token, (*data)->line_len - *i, j);
}
