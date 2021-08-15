#include "minishell.h"
#include "lexer.h"
#include "libft.h"

char	*is_meta(char c)
{
	return (ft_strchr(META_CHAR, c));
}

char	*is_expansion(char c)
{
	return (ft_strchr(EXPANSION_CHAR, c));
}

int	is_valid_expansion(char *str)
{
	return (str[0] == '$' && str[1] && ft_isalnum(str[1]));
}

char	*is_quote(char c)
{
	return (ft_strchr(QUOTE_CHAR, c));
}

int	is_quote_edge_case(t_data *data, size_t i)
{
	char	c;
	char	next;

	if (data->line[i + 1] == 0)
		return (0);
	c = data->line[i];
	next = data->line[i + 1];
	return (c == '$' && is_quote(next));
}