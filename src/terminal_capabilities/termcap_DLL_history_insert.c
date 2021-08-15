#include "minishell_termcap_signal.h"

void	insert_node_history_start(t_history **lst, t_history *node)
{
	if (*lst == NULL)
		*lst = node;
	else
	{
		(*lst)->previus = node;
		node->next = *lst;
		*lst = (*lst)->previus;
	}
}
