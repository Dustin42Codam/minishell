#include "minishell.h"
#include "executor.h"

void	execute_pipeline(t_data *data)
{
	if (data->astree == NULL)
		return ;
	execute_command(data);
}

void	execute_command(t_data *data)
{
	t_command	command;

	if (data->astree == NULL)
		return ;
	make_command_argv(data, data->astree, &command);
	if (command.builtin_id)
		data->exit_status = execute_builtin(&command, data->env);
	else
		data->exit_status = execute_command_argv(&command, data->env);
}

void	execute(t_data *data)
{
	execute_pipeline(data);
}
