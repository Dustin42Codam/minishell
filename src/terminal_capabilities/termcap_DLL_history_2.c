#include "minishell_termcap_signal.h"
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

bool	is_string_NULL(char *str)
{
	if (str == NULL)
		return (true);
	else
		return (false);
}
