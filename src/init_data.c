#include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

void	free_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	free(data->env);
	data->env = NULL;
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	free(data);
	data = NULL;
}

char	**copy_envp(char **envp)
{
	size_t	len;
	char	**copy;

	len = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[len])
		len++;
	copy = (char **)secure_calloc(len + 1, sizeof(char *));
	len = 0;
	while (envp[len])
	{
		copy[len] = ft_strdup(envp[len]);
		if (errno)
			exit_shell(errno);
		len++;
	}
	return (copy);
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)secure_calloc(1, sizeof(t_data));
	data->env = copy_envp(envp);
	return (data);
}
