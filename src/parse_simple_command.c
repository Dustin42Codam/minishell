#include "minishell.h"
#include "libft.h"
#include <errno.h>

/**
 * 	<simple command>::=		<pathname> <token list>
**/
t_astree	*parse_simple_command(t_data *data)
{
	// t_astree	*simple_cmd_node;
	t_astree	*token_list;
	t_astree	*simple_command;
	t_token		*save;
	char		*pathname;

	save = data->token_ptr;

	if (get_next_token(data, &pathname, WORD))
	{
		data->token_ptr = save;
		return (NULL);
	}

	token_list = parse_token_list(data);

	simple_command = (t_astree *)ft_calloc(1, sizeof(t_astree));
	if (errno)
		exit_shell(errno);
	init_ast_node(simple_command, pathname, AST_CMD);
	insert_ast_node(simple_command, NULL, token_list);

	return (simple_command);
}

/**
 * 	<token list>	::=		<token> <token list>
 * 					|		<NULL>
**/

t_astree	*parse_token_list(t_data *data)
{
	t_astree	*token_list_node;
	t_token		*save;


	save = data->token_ptr;
	token_list_node = parse_tokens(data);
	if (token_list_node)
		return (token_list_node);

	return (NULL);
}

t_astree	*parse_tokens(t_data *data)
{
	t_astree	*child_token;
	t_astree	*parent_token;
	char		*token_str;
	t_token		*save;

	save = data->token_ptr;
	if (get_next_token(data, &token_str, WORD))
	{
		data->token_ptr = save;
		return (NULL);
	}

	child_token = parse_token_list(data);

	parent_token = (t_astree *)ft_calloc(1, sizeof(t_astree));
	if (errno)
		exit_shell(errno);

	init_ast_node(parent_token, token_str, AST_CMD_ARG);
	insert_ast_node(parent_token, NULL, child_token);
	
	return (parent_token);
}
