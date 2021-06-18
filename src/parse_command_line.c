#include "minishell.h"
#include "libft.h"
#include <errno.h>

/**
 *	
 *	<command line>	::=		<job> ';' <command line>
 * 					|		<job> ';'
 * 					|		<job>
**/
t_astree	*parse_command_line(t_data *data)
{
	t_astree	*command_line;
	t_token		*save;

	save = data->token_ptr;			/**
									* save token_ptr so it is possible
									* to call different functions recursively
									* with the initial state of data->token_ptr value.
									**/

	command_line = parse_cmd_line_sequence(data);
	if (command_line)
		return (command_line);

	data->token_ptr = save;
	command_line = parse_cmd_line_semi(data);
	if (command_line)
		return (command_line);

	data->token_ptr = save;
	command_line = parse_job(data);
	if (command_line)
		return (command_line);
	

	/**
	 * return NULL if all grammar checks failed
	 * which means that user input contains
	 * incorrect syntax
	 * */
	return (NULL);
}

/**
 *	<command line>	::=		<job> ';' <command line>
**/
t_astree	*parse_cmd_line_sequence(t_data *data)
{
	t_astree	*command_line;
	t_astree	*semicolon;
	t_astree	*job;
	t_token		*save;

	save = data->token_ptr;

	job = parse_command(data);
	
	if (get_next_token(data, NULL, SEMICOLON))
	{
		delete_ast(job);
		return (NULL);
	}

	command_line = parse_command_line(data);

	semicolon = (t_astree *)ft_calloc(1, sizeof(t_astree));
	if (errno)
		exit_shell(errno);

	init_ast_node(semicolon, NULL, AST_LIST);
	insert_ast_node(semicolon, job, command_line);

	return (semicolon);
}

/**
 *	<command line>	::=		<job> ';'
**/
t_astree	*parse_cmd_line_semi(t_data *data)
{
	t_astree	*job;
	t_astree	*command_line;
	t_token		*save;

	save = data->token_ptr;

	job = parse_job(data);
	
	if (get_next_token(data, NULL, SEMICOLON))
	{
		delete_ast(job);
		return (NULL);
	}

	command_line = (t_astree *)ft_calloc(1, sizeof(t_astree));
	if (errno)
		exit_shell(errno);

	init_ast_node(command_line, NULL, AST_LIST);
	insert_ast_node(command_line, job, NULL);

	return (command_line);
}
