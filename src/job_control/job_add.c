/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 11:07:48 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/15 14:26:48 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <stdlib.h>

void	job_add(t_data *data, pid_t pid, t_command *cmd)
{
	t_job	*tmp;
	t_job	*new;

	if (data == NULL || pid == 0)
		return ;
	tmp = data->job;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	new = (t_job *)minishell_calloc(1, sizeof(t_job));
	new->pid = pid;
	new->cmd = cmd;
	if (data->job == NULL)
		data->job = new;
	else
		tmp->next = new;
}
