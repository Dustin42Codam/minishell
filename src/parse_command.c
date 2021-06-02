#include "minishell.h"
#include "libft.h"
#include <errno.h>

/**
 * 	<command>	::=		<simple command> '<' <filename>
 *				|		<simple command> '>' <filename>
 *				|		<simple command>
**/

t_astree	*parse_command(t_data *data)
{
	t_astree	*command;
	t_token		*save;

	save = data->token_ptr;

	command = parse_command_redir_in(data);
	if (command)
		return (command);

	data->token_ptr = save;
	command = parse_command_redir_out(data);
	if (command)
		return (command);

	data->token_ptr = save;
	command = parse_simple_command(data);
	if (command)
		return (command);

	return (NULL);
}

/**
 * 	<command>	::=		<simple command> '<' <filename>
**/
t_astree	*parse_command_redir_in(t_data *data)
{
	t_astree	*operator;
	t_astree	*simple_command;
	char		*filename;

	simple_command = parse_simple_command(data);
	if (get_next_token(data, NULL, REDIR_IN))
	{
		delete_ast(simple_command);
		return (NULL);
	}
	if (get_next_token(data, &filename, WORD))
	{
		delete_ast(simple_command);
		return (NULL);
	}
	operator = (t_astree *)ft_calloc(1, sizeof(t_astree));
	if (errno)
		exit_shell(errno);
	init_ast_node(operator, filename, AST_REDIR_IN);	//test redundancy with AST_REDIR_IN
	insert_ast_node(operator, NULL, simple_command);
	return (operator);
}

/**
 * 	<command>	::=		<simple command> '>' <filename>
**/
t_astree	*parse_command_redir_out(t_data *data)
{
	t_astree	*operator;
	t_astree	*simple_command;
	char		*filename;

	simple_command = parse_simple_command(data);
	if (get_next_token(data, NULL, REDIR_OUT))
	{
		delete_ast(simple_command);
		return (NULL);
	}
	if (get_next_token(data, &filename, WORD))
	{
		delete_ast(simple_command);
		return (NULL);
	}
	operator = (t_astree *)ft_calloc(1, sizeof(t_astree));
	if (errno)
		exit_shell(errno);
	init_ast_node(operator, filename, AST_REDIR_OUT);	//test redundancy with AST_REDIR_IN
	insert_ast_node(operator, NULL, simple_command);
	return (operator);
}
