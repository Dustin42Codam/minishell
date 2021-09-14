#include "minishell.h"
#include "executor.h"

#include <stdlib.h>

static void	free_command(t_command *command)
{
	size_t	i;

	i = 0;
	while (command->argv && command->argv[i])
	{
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
}

void	execute_word_list(t_data *data, t_astree *node, t_file_io fd)
{
	t_command	command;

	if (node == NULL)
		return ;
	make_command(data, node, &command, fd);
	if (command.builtin_id)
	{
		execute_builtin(data, &command, data->env);
		free_command(&command);
	}
	else
		execute_command_argv(data, &command, data->env);
}
