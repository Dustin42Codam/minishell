#include "minishell_termcap_signal.h"
#include "minishell.h"

#include <stdio.h>
#include <errno.h>

t_signals	*get_last_signal(t_signals *lst)
{
	static const t_signals	*end_of_list = NULL;

	while (lst->next != end_of_list)
		lst = lst->next;
	return (lst);
}

void	add_signal_back(t_signals **head, t_signals *new)
{
	t_signals	*tmp;

	if (head == NULL)
		exit_minishell_custom("Some things went horribly worng init_sig\n");
	if (*head == NULL)
		*head = new;
	else 
	{
		tmp = get_last_signal(*head);
		tmp->next = new;
	}
}

t_signals	*new_signal(char c, int signal_NO, void (*hook_function)(int))
{
	static const t_signals	*ft_calloc_failed = NULL;
	t_signals		*new_signal;

	new_signal = ft_calloc(sizeof(t_signals), 1);
	if (new_signal == ft_calloc_failed)
		exit_minishell(errno);
	new_signal->next = NULL;
	new_signal->signal_char = c;
	new_signal->signal_NO = signal_NO;
	new_signal->hook_function = hook_function;
	return (new_signal);
}

/*
**	cast to int SIGINT ->|2| SIGQUIT ->|3| EOF-> |-1|
*/

t_signals	*init_signals(void)
{
	t_signals	*head;

	head = NULL;
	/*add_signal_back(head, new_signal(3, SIGINT, &hook_sigint));
	add_signal_back(head, new_signal(28, SIGQUIT, &hook_sigquit));
	add_signal_back(head, new_signal(4, EOF, &hook_sigint));
	add_signal_back(head, new_signal(5, -2, &hook_jump_right));
	add_signal_back(head, new_signal(1, -3, &hook_jump_left));*/
	add_signal_back(&head, new_signal(3, SIGINT, NULL));
	add_signal_back(&head, new_signal(28, SIGQUIT, NULL));
	add_signal_back(&head, new_signal(4, EOF, NULL));
	add_signal_back(&head, new_signal(5, -2, NULL));
	add_signal_back(&head, new_signal(1, -3, NULL));
	return (head);
}
