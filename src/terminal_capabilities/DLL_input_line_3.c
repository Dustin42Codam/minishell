#include "terminal_capabilities.h"
#include "minishell.h"

#include <errno.h>

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

void	insert_pad_node_input_line(t_input_line **lst, t_input_line *node)
{
	(*lst)->next = node;
	node->previus = (*lst);
	*lst = (*lst)->next;
}

void	insert_node_input_line(t_input_line **lst, t_input_line *node)
{
	t_input_line	*previus;

	if (node == NULL)
		exit_minishell(errno);
	if (*lst == NULL)
	{
		*lst = node;
		insert_pad_node_input_line(lst, new_input_line_node('\0'));
		return ;
	}
	else if ((*lst)->previus == NULL)
	{
		(*lst)->previus = node;
		node->next = *lst;
	}
	else
	{
		previus = (*lst)->previus;
		previus->next = node;
		node->previus = previus;
		(*lst)->previus = node;
		node->next = *lst;
	}
}
