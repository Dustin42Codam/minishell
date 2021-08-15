#include "minishell_termcap_signal.h"

#include <stdlib.h>

void	delete_history_node(t_history **node)
{
	free(*node);
	*node = NULL;
}
