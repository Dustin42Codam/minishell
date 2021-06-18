#include "minishell.h"

/**
* <command line>	::= 	<job> ';' <command line>	// not ready
* 					|		<job> ';'					// not ready
* 							<job>						// basics ready
**/
void	execute_command_line(t_data *data)
{
	if (data->astree == NULL)
		return ;
	if (data->astree->type & AST_LIST)
	{
		execute_job(data);
		execute_command_line(data);
	}
	else
	{
		execute_job(data);
	}
}

/**
 * <job>	::=	<command> '|' <job>		// not ready
 * 			 |	<command>				// basics ready
 **/
void	execute_job(t_data *data)
{
	if (data->astree == NULL)
		return ;
	else if (data->astree->type & AST_CMD)
		execute_command(data);

}

/**
 * 	<command>	::=		<simple command> '<' <filename> // not ready
 *				|		<simple command> '>' <filename> // not ready
 *				|		<simple command>				// basics ready
**/
void	execute_command(t_data *data)
{
	if (data->astree == NULL)
		return ;
	else if (data->astree->type & AST_CMD)
		execute_simple_command(data);
	(void)data;
}

/**
 * 	<simple command>::=		<pathname> <token list>
**/
void	execute_simple_command(t_data *data)
{
	t_command	command;

	make_command_argv(data->astree, &command);
	execute_command_argv(&command, data->env);
}

/**
 * 	Root function that will try to execute the AST
 * 	following the syntax rules.
**/
void	execute(t_data *data)
{
	execute_command_line(data);
}
