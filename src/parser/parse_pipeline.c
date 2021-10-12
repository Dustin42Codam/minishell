#include "minishell.h"
#include "parser.h"
#include "lexer.h"

/**
 *	parse_pipeline - creates a AST node for a <pipeline>
 *
 *	A <pipeline> can either consist of a sequence of pipes 
 *	-> 'echo 1 | grep "1" | wc -l'
 *	or an open pipe ->	'echo abc | '.
 *	or just a single command -> 'echo -n "abc"'
 *
 *  Grammar:
 * 	<pipeline>	::=		<command> '|' <pipeline>
 *				|		<pipeline> '|'
 *				|		<command>
**/
t_astree	*parse_pipeline(t_data *data)
{
	t_astree	*pipeline;
	t_token		*token_backup;

	token_backup = data->token_ptr;
	pipeline = parse_pipe_sequence(data);
	if (pipeline)
	{
		if (data->token_ptr->type & (HERE_DOC | REDIR_IN | APPEND | REDIR_OUT) ||
			(data->token_ptr && data->token_ptr->type & PIPE))
		{
			delete_ast(pipeline);
			pipeline = NULL;
		}
		return (pipeline);
	}
	data->token_ptr = token_backup;
	pipeline = parse_command(data);
	if (pipeline)
	{
		if (data->token_ptr->type & (HERE_DOC | REDIR_IN | APPEND | REDIR_OUT) ||
			(data->token_ptr->next && data->token_ptr->next->type & PIPE))
		{
			delete_ast(pipeline);
			pipeline = NULL;
		}
		return (pipeline);
	}
	return (NULL);
}

/**
 *	<pipeline>	::=		<command> '|' <pipeline>
 *				|		<pipeline> '|'
**/
t_astree	*parse_pipe_sequence(t_data *data)
{
	t_astree	*parent_pipeline;
	t_astree	*child_pipeline;
	t_astree	*command;

	command = parse_command(data);
	if (!command)
		return (NULL);
	if (get_next_token(data, NULL, PIPE))
	{
		delete_ast(command);
		return (NULL);
	}
	child_pipeline = parse_pipeline(data);
	parent_pipeline = (t_astree *)minishell_calloc(1, sizeof(t_astree));
	init_ast_node(parent_pipeline, NULL, AST_PIPE);
	insert_ast_node(parent_pipeline, command, child_pipeline);
	return (parent_pipeline);
}
