#include "minishell.h"
#include "lexer.h"

/**
 * empty_quotes()
 * checks if a quote follows another quote of the same type ("" or '')
 * This will enable the token to be recognized
 * by the parser as an empty argument.
 * Returns TRUE if empty quotes were detected
 * and FALSE in any other case.
**/
int	empty_quotes(char *line, size_t i, size_t *j)
{
	if (is_quote(line[i]) && line[i] == line[i - 1])
	{
		(*j)++;
		return (TRUE);
	}
	return (FALSE);
}

/**
 * make_token_squote()
 * - ORs the token type with SQUOTE
 * - checks for empty single quotes
 * - when no empty single quotes are detected it tries to copy characters
 * 		up until a matching single quote has been found.
 * - at the end of the loop there is a check if the end of the input
 * 		line has been reached. This means that the quotes are open
 * 		(e.g.: echo 'lol ). The error variable is set to TRUE and
 * 		the calling function will know about the syntax error.
 * -	ORs the token type with WORD.	  
**/
void	make_token_squote(t_token **token, t_data **data, size_t *i, size_t *j)
{
	char	*line;

	line = (*data)->line;
	(*token)->type |= SQUOTE;
	(*i)++;
	if (empty_quotes(line, *i, j) == TRUE)
		return ;
	while (line[(*i)] && line[(*i)] != '\'')
	{
		(*token)->str[(*j)] = line[(*i)];
		(*i)++;
		(*j)++;
		if (line[(*i)] == '\0')
			(*data)->error = TRUE;
	}
	(*token)->type |= WORD;
}

/**
 * make_token_dquote()
 * - ORs the token type with DQUOTE
 * - checks for empty double quotes
 * - when no empty double quotes are detected it tries to copy characters
 * 		up until a matching double quote has been found.
 * - if a '$' is present this method ORs the token type with EXPAND value.
 * 		this will allow to do variable expansion before commmand execution.
 * - at the end of the loop there is a check if the end of the input
 * 		line has been reached. This means that the quotes are open
 * 		(e.g.: echo "lol ). The error variable is set to TRUE and
 * 		the calling function will know about the syntax error.
 * -	ORs the token type with WORD.
**/
void	make_token_dquote(t_token **token, t_data **data, size_t *i, size_t *j)
{
	char	*line;

	line = (*data)->line;
	(*token)->type |= DQUOTE;
	(*i)++;
	if (empty_quotes(line, *i, j) == TRUE)
		return ;
	while (line[(*i)] && line[(*i)] != '\"')
	{
		if (is_valid_expansion((*data)->line + (*i)))
			(*token)->type |= EXPAND;
		(*token)->str[(*j)] = line[(*i)];
		(*i)++;
		(*j)++;
		if (line[(*i)] == '\0')
			(*data)->error = TRUE;
	}
	(*token)->type |= WORD;
}

void	make_token_quote(t_token **token, t_data **data, size_t *i, size_t *j)
{
	char	c;

	c = (*data)->line[(*i)];
	if (c == '\'')
		make_token_squote(token, data, i, j);
	else if (c == '\"')
		make_token_dquote(token, data, i, j);
	(*data)->token_mask |= (*token)->type;
	init_new_token(token, (*data)->line_len - *i, j);
}
