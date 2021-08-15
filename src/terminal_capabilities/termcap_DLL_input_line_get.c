#include "minishell_termcap_signal.h"
#include "minishell.h"

#include <limits.h>

int	get_size_of_input_line_dll(t_input_line *lst)
{
	int	index;
	static const int	MAX_LINE_LENGTH = INT_MAX;

	index = 0;
	while (lst)
	{
		index++;
		if (index == MAX_LINE_LENGTH)
			exit_minishell_custom("line to long\n");
		lst = lst->next;
	}
	return (index);
}

t_input_line	*get_head_of_input_line(t_input_line *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->previus != NULL)
		lst = lst->previus;
	return (lst);
}
