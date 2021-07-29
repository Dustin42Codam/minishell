#include "minishell.h"
#include "libft.h"
#include "environ.h"
#include <errno.h>
#include <stdlib.h>

void	free_data(t_data *data)
{
	environ_free(data->env);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	free(data);
	data = NULL;
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)minishell_calloc(1, sizeof(t_data));
	data->env = environ_deep_copy(envp);
	data->exit_status = 123;
	increment_shlvl(data->env);
	return (data);
}
