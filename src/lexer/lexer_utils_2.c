#include "lexer.h"
#include "libft.h"

int	get_token_type(char *s)
{
	if (s[0] == ' ')
		return (WORD);
	else if (s[0] == '|')
		return (PIPE);
	else if (s[0] == '<' && s[1] == '<')
		return (HERE_DOC);
	else if (s[0] == '<')
		return (REDIR_IN);
	else if (s[0] == '>' && s[1] == '>')
		return (APPEND);
	else if (s[0] == '>')
		return (REDIR_OUT);
	else if (s[0] == '$')
		return (EXPAND);
	else if (s[0] == '\'')
		return (SQUOTE);
	else if (s[0] == '\"')
		return (DQUOTE);
	return (EMPTY);
}

int	is_special_expansion(char *str)
{
	return (str[0] == '$' && str[1] && str[1] == '?');
}

char	*is_blank(char c)
{
	return (ft_strchr(BLANK_CHAR, c));
}

char	*is_break(char c)
{
	return (ft_strchr(BREAK_CHAR, c));
}

void	get_exit_status(t_data **data, t_token **token, size_t *i, size_t *j)
{
	size_t	index;
	char	*str;

	index = 0;
	str = ft_itoa((*data)->exit_status);
	while (str[index])
	{
		(*token)->str[(*j)] = str[index];
		(*j)++;
		index++;
	}
	(*i)++;
	(*token)->type |= WORD;
}
