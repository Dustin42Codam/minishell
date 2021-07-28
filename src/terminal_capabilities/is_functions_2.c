#include "terminal_capabilities.h"
#include "libft.h"

bool	is_str_key(char *key, char *c, int size_of_key)
{
	if (ft_strncmp(key, c, size_of_key) == false)
		return (true);
	else
		return (false);
}

bool	is_cursor_at_lats_column(t_prompt prompt, int col)
{
	if (prompt.max_col == col)
		return (true);
	else
		return (false);
}
