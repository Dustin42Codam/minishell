#include "minishell.h"
#include <stdlib.h>
#include <signal.h>

void	free_child_pid(t_child *head)
{
	t_child	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
