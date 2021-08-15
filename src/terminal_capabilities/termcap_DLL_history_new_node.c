#include "minishell_termcap_signal.h"
#include "minishell.h"

#include <errno.h>

t_history	*new_history_node(char *str)
{
	t_history	*new;

	if (str == NULL)
		exit_minishell(errno);
	new = minishell_calloc(sizeof(t_history), 1);
	new->previus = NULL;
	new->next = NULL;
	new->str = str;
	return (new);
}
