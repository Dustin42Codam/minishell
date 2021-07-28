#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <errno.h>

t_input_line	*new_input_line_node(char c)
{
	t_input_line	*new;

	new = ft_calloc(sizeof(t_input_line), 1);
	if (new == NULL)
		exit_minishell(errno);
	new->previus = NULL;
	new->next = NULL;
	new->c = c;
	return (new);
}
