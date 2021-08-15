#include "minishell_termcap_signal.h"
#include <stdio.h>

/*
**	2     SIGINT       terminate process    interrupt program
**	3     SIGQUIT      create core image    quit program
**	-1    EOF          close file descriptor
*/

int	call_function_by_sig(char *user_input, t_prompt *prompt)
{
	static const int	DID_NOT_FIND_SIGNAL = 42;
	static const int	EMPTY = 2;
	t_signals		*tmp;
	t_input_line		*head;

	head = get_head_of_input_line(prompt->input_line);
	tmp = prompt->signals;
	while (tmp)
	{
		if (tmp->signal_char == (int)*user_input)
		{
			if (tmp->signal_NO == EOF || tmp->signal_NO == SIGQUIT)
			{
				if (get_size_of_input_line_dll(head) >= EMPTY)
				{
					ring_bell();
					return (DID_NOT_FIND_SIGNAL);
				}
			}
			return (tmp->signal_NO);
		}
		tmp = tmp->next;
	}
	return (DID_NOT_FIND_SIGNAL);
}
