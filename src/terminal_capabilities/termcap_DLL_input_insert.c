#include "minishell_termcap_signal.h"
#include "minishell.h"

#include <errno.h>

void	insert_pad_node_input_line(t_input_line **lst, t_input_line *node)
{
	(*lst)->next = node;
	node->previus = (*lst);
	*lst = (*lst)->next;
}

/*
**	node can bee nule because if malloc fials from ft_strdup fomr libft
*/

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
