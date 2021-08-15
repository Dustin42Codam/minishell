#include "minishell_termcap_signal.h"

bool	is_next_history_node_null(t_prompt *prompt)
{
	if (prompt->history->next == NULL)
		return (true);
	else
		return (false);
}

bool	is_previus_history_node_null(t_prompt *prompt)
{
	if (prompt->history->previus == NULL)
		return (true);
	else
		return (false);
}

bool	is_history_null(t_prompt *prompt)
{
	if (prompt->history == NULL)
		return (true);
	else
		return (false);
}

bool	is_next_prev_node_null(t_prompt *prompt)
{
	if (prompt->history->next == NULL)
		return (true);
	else if (prompt->history->previus == NULL)
		return (true);
	else
		return (false);
}
