#include "minishell_termcap_signal.h"

bool	is_previus_previus_input_line_node_NULL(t_input_line *input_line)
{
	if (input_line->previus->previus == NULL)
		return (true);
	else
		return (false);
}

bool	is_next_input_line_node_null(t_prompt *prompt)
{
	if (prompt->input_line->next == NULL)
		return (true);
	else
		return (false);
}

bool	is_input_line_node_null(t_prompt *prompt)
{
	if (prompt->input_line == NULL)
		return (true);
	else
		return (false);
}

bool	is_next_input_node_null(t_input_line *node)
{
	if (node == NULL)
		return (false);
	if (node->next == NULL)
		return (true);
	else
		return (false);
}

bool	is_previus_input_line_node_null(t_input_line *node)
{
	if (node == NULL)
		return (false);
	if (node->previus == NULL)
		return (true);
	else
		return (false);
}
