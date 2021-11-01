/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:57:03 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/27 13:09:28 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include "libft.h"
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

t_data	*init_data(char **envp, char *path)
{
	t_data	*data;
	t_environ *new;

	data = (t_data *)minishell_calloc(1, sizeof(t_data));
	data->env = environ_deep_copy(envp);
	increment_shlvl(data->env);
	new = environ_new(ft_strjoin("SHELL=", path));	// check strjoin
	environ_modify(&data->env, new);
	data->fd = (t_file_io *)minishell_calloc(1, sizeof(t_file_io));
	return (data);
}
