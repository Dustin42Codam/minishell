#include "minishell_termcap_signal.h"
#include "minishell.h"
#include "libft.h"

#include <errno.h>

t_input_line	*new_input_line_node(char c)
{
	t_input_line	*new;

	new = minishell_calloc(sizeof(t_input_line), 1);
	new->previus = NULL;
	new->next = NULL;
	new->c = c;
	return (new);
}
