#include "minishell.h"
#include "libft.h"
#include <errno.h>

int	get_token_id(char c)
{
	if (c == ' ')
		return (WORD);
	else if (c == '\'')
		return (SQUOTE);
	else if (c == '\"')
		return (DQUOTE);
	else if (c == ';')
		return (SEMICOLON);
	else if (c == '|')
		return (PIPE);
	else if (c == '<' || c == '>')
		return (REDIR);
	return (-1);
}

int	check_quotes(char *line, size_t line_len, size_t i)
{
	int	open;

	open = 0;
	while (line[i] && i != line_len)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int	token_quote(t_token **token, t_data **data, size_t *i, char c)
{
	char	*next_quote;

	if (check_quotes((*data)->line, (*data)->line_len, (*i)))
		return (1);
	next_quote = ft_strchr((*data)->line + (*i) + 1, c);
	ft_strlcpy((*token)->str, (*data)->line + (*i) + 1, \
				next_quote - ((*data)->line + (*i)));
	(*token)->id = get_token_id(c);
	(*i) += ft_strlen((*token)->str) + 1;
	init_next_token(token, (*data)->line_len, *i);
	return (0);
}

int	token_meta(t_token **token, t_data **data, size_t *i, char c)
{
	(*token)->str[0] = c;
	if (c == '>' && (*data)->line[(*i) + 1] == '>')
	{
		(*i)++;
		(*token)->str[1] = '>';
	}
	if ((*data)->line[(*i) + 1] == c)
		return (1);
	(*token)->id = get_token_id(c);
	init_next_token(token, (*data)->line_len, *i);
	return (0);
}
