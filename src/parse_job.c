#include "minishell.h"
#include "libft.h"
#include <errno.h>

/**
 * <job>	::=	<command> '|' <job>
 * 			 |	<command>
 **/
t_astree	*parse_job(t_data *data)
{
	t_astree	*job;
	t_token		*save;

	save = data->token_ptr;

	job = parse_job_pipeline(data);
	if (job)
		return (job);

	data->token_ptr = save;
	job = parse_command(data);
	if (job)
		return (job);

	save = data->token_ptr;

	return (NULL);
}

/**
 * <job>	::=	<command> '|' <job>
 **/
t_astree	*parse_job_pipeline(t_data *data)
{
	t_astree	*operator;
	t_astree	*command;
	t_astree	*job;

	command = parse_command(data);

	if (get_next_token(data, NULL, PIPE))
	{
		delete_ast(command);
		return (NULL);
	}

	job = parse_job(data);

	operator = (t_astree *)ft_calloc(1, sizeof(t_astree));
	if (errno)
		exit_shell(errno);
	init_ast_node(operator, NULL, AST_PIPE);
	insert_ast_node(operator, command, job);
	return (operator);
}
