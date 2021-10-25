#include "minishell.h"
#include <stdlib.h>
#include <signal.h>

static void	free_first_node(t_child **head, t_child **tmp_fast)
{
	free(*head);
	*head = *tmp_fast;
}

static void	free_last_node(t_child **head, t_child **tmp)
{
	if ((*tmp)->next == NULL)
	{
		free(*head);
		*head = NULL;
	}
	else
	{
		free(*head);
		*head = *tmp;
	}
}

static void	free_mid_node(t_child **head, t_child **tmp_fast, t_child **tmp_slow, t_child **tmp)
{
	free(*head);
	(*tmp_slow)->next = *tmp_fast;
	*head = *tmp;
}

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
				return (free_last_node(head, &tmp));
			else if (tmp_slow == NULL)
				return (free_first_node(head, &tmp_fast));
			else
				return (free_mid_node(head, &tmp_fast, &tmp_slow, &tmp));
		}
		else
		{
			tmp_slow = *head;
			*head = (*head)->next;
		}
	}
}
