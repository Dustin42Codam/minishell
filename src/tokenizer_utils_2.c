#include "minishell.h"
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
	return (ft_strchr(EXP_CHAR, c));
}

char	*is_bsdquote(char c)
{
	return (ft_strchr(BSDQUOTE_CHAR, c));
}
