#include "minishell.h"
#include "lexer.h"
#include "libft.h"

char	*is_meta(char c)
{
	return (ft_strchr(META_CHAR, c));
}

char	*is_break(char c)
{
	return (ft_strchr(BREAK_CHAR, c));
}

char	*is_quote(char c)
{
	return (ft_strchr(QUOTE_CHAR, c));
}

char	*is_expansion(char c)
{
	return (ft_strchr(EXPANSION_CHAR, c));
}

int	is_valid_expansion(char *str)
{
	return (str[0] == '$' && str[1] && str[1] != ' ');
}
