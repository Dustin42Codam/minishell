#include "minishell.h"
#include "executor.h"

void	execute_word_list(t_data *data, t_astree *node, t_file_io fd)
{
	t_command	command;

	if (node == NULL)
		return ;
	make_command_argv(data, node, &command, fd);
	if (command.builtin_id)
		data->exit_status = execute_builtin(&command, data->env);
	else
		data->exit_status = execute_command_argv(&command, data->env);
}
