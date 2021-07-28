#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void	move_history_to_start(t_prompt **prompt)
{
	while ((*prompt)->history->previus != NULL)
		(*prompt)->history = (*prompt)->history->previus;
}

void	update_tmp_history(t_prompt **prompt)
{
	char	*str;

	str = copy_input_line((*prompt)->input_line);
	if (is_string_NULL(str) == true)
		exit_minishell(errno);
	free((*prompt)->tmp_history);
	(*prompt)->tmp_history = str;
}

bool	is_string_NULL(char *str)
{
	if (str == NULL)
		return (true);
	else
		return (false);
}

void	update_history_node(t_history **dest, char *src)
{
	free((*dest)->str);
	(*dest)->str = ft_strdup(src);
	if (is_string_NULL((*dest)->str) == true)
		exit_minishell(errno);
}
