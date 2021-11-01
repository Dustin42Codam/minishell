/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:57:03 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/30 13:10:50 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include <stdlib.h>

void	free_data(t_data *data)
{
	environ_free(data->env);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	free(data->fd);
	free(data);
	data = NULL;
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)minishell_calloc(1, sizeof(t_data));
	data->env = environ_deep_copy(envp);
	increment_shlvl(data->env);
	data->fd = (t_file_io *)minishell_calloc(1, sizeof(t_file_io));
	return (data);
}
