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
		i++;
	}
	free(data->env);
	free(data);
}

char	**copy_envp(char **envp)
{
	size_t	len;
	char	**copy;

	len = 0;
	while (envp[len])
		len++;
	copy = (char **)ft_calloc(len + 1, sizeof(char *));
	if (errno)
		exit_shell(errno);
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

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (errno)
		exit_shell(errno);
	data->env = copy_envp(envp);
	return (data);
}
