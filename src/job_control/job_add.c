/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_add.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 11:07:48 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/15 12:26:03 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

void	job_add(t_data *data, int pid)
{
	t_job	*tmp;

	if (data == NULL || pid = 0)
		return ;
	tmp = data->job;
	
	while (tmp)
	{
		tmp = tmp->next;
	}
}
