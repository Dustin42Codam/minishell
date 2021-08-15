#include "minishell.h"
#include "executor.h"

void	execute_word_list(t_data *data, t_astree *node, t_file_io fd)
{
	t_command	command;

	if (node == NULL)
		return ;
	make_command(data, node, &command, fd);
	if (command.builtin_id)
		execute_builtin(data, &command, data->env);
	else
		execute_command_argv(data, &command, data->env);
}
