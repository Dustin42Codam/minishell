#include "minishell.h"
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

char	*is_specvar(char c)
{
	return (ft_strchr(SPECIAL_VAR_CHAR, c));
}

char	*is_blank(char c)
{
	return (ft_strchr(BLANK_CHAR, c));
}

char	*is_end(char c)
{
	return (ft_strchr(END_CHAR, c));
}
