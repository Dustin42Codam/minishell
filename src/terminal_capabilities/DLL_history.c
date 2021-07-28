#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <errno.h>

void	delete_history_node(t_history **node)
{
	free(*node);
	*node = NULL;
}

t_history	*new_history_node(char *str)
{
	t_history	*new;

	if (str == NULL)
		exit_minishell(errno);
	new = ft_calloc(sizeof(t_history), 1);
	if (new == NULL)
		exit_minishell(errno);
	new->previus = NULL;
	new->next = NULL;
	new->str = str;
	return (new);
}

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

void	update_node(t_prompt **prompt, char *updated_line)
{
	if (updated_line == NULL)
		exit_minishell(errno);
	free((*prompt)->history->str);
	(*prompt)->history->str = updated_line;
}

void	update_line(t_prompt **prompt)
{
	char	*str;

	str = copy_input_line((*prompt)->input_line);
	update_node(prompt, str);
}
