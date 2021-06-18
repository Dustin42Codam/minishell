#include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

int	get_next_token(t_data *data, char **token_str, int token_type)
{
	if (data->token_ptr->type == EMPTY)
		return (EXIT_FAILURE);
	else if (data->token_ptr->type == token_type)
	{
		if (token_str)
		{
			*token_str = ft_strdup(data->token_ptr->str);
			if (errno)
				exit_shell(errno);
		}
		data->token_ptr = data->token_ptr->next;
		return (EXIT_SUCCESS);
	}

	/**
	 * end of parsing a token list when token_ptr
	 * points to a token of a different type.
	 * echo 123 abc;
	**/
	data->token_ptr = data->token_ptr->next;
	return (EXIT_FAILURE);
}

void	parse_astree(t_data *data)
{
	data->token_ptr = data->token;
	data->astree = parse_command_line(data);
}
