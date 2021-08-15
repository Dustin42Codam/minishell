#include "minishell_termcap_signal.h"
#include <stdlib.h>

void	delete_input_line_node(t_input_line **node)
{
	free(*node);
	*node = NULL;
}

void	clear_input_line(t_input_line **line)
{
	t_input_line	*tmp;

	if (*line == NULL)
		return ;
	while ((*line)->next)
	{
		tmp = (*line)->next;
		delete_input_line_node(line);
		*line = tmp;
	}
	delete_input_line_node(line);
}
