#include "minishell.h"
#include <stdlib.h>
#include <signal.h>

void	free_child_pid(t_child **head, pid_t pid)
{
	t_child	*tmp_slow;
	t_child	*tmp_fast;
	t_child	*tmp;

	tmp = *head;
	tmp_slow = NULL;
	while (*head)
	{
		if (pid == (*head)->pid)
		{
			tmp_fast = (*head)->next;
			if ((*head)->next == NULL)
			{
				free(*head);
				*head = NULL;
				return ;
			}
			else if (tmp_slow == NULL)
			{
				free(*head);
				*head = tmp_fast;
			}
			else
			{
				free(*head);
				tmp_slow->next = tmp_fast;
			}
			break ;
			*head = tmp;
		}
		else
		{
			tmp_slow = *head;
			*head = (*head)->next;
		}
	}
}
