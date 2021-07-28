#include "terminal_capabilities.h"
#include "minishell.h"

#include <stdlib.h>
#include <limits.h>

void	delete_input_line_node(t_input_line **node)
{
	free(*node);
	*node = NULL;
}

void	pop_a_node_input_line_start(t_input_line **current)
{
	t_input_line	*previus;

	previus = (*current)->previus;
	delete_input_line_node(&previus);
	(*current)->previus = NULL;
}

void	pop_a_node_input_line_midle(t_input_line **current)
{
	t_input_line	*previus_previus_node;
	t_input_line	*previus_node;

	previus_previus_node = (*current)->previus->previus;
	previus_node = (*current)->previus;
	delete_input_line_node(&previus_node);
	previus_previus_node->next = *current;
	(*current)->previus = previus_previus_node;
}

int	size_of_input_line_dll(t_input_line *lst)
{
	int	index;

	index = 0;
	while (lst)
	{
		index++;
		if (index == INT_MAX)
			exit_minishell_custom("line to long\n");
		lst = lst->next;
	}
	return (index);
}
