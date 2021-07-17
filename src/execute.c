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
	execute_command_argv(&command, data->env);
}

/**
 * 	Root function that will try to execute the AST
 * 	following the syntax rules.
**/
void	execute(t_data *data)
{
	execute_pipeline(data);
}
