#include "minishell_termcap_signal.h"

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

void	pop_a_node_input_line(t_input_line **lst)
{
	if (*lst == NULL)
		return ;
	if (is_previus_input_line_node_null(*lst) == true)
		return ;
	else if (is_previus_previus_input_line_node_NULL(*lst) == true)
		pop_a_node_input_line_start(lst);
	else
		pop_a_node_input_line_midle(lst);
}
