#include "minishell.h"
#include "parser.h"

/**
 * parse_command - creates a AST node for a <command>
 *
 * A <command> consists of words (echo "abc" "123"),
 * or of redirections (echo "abc" > file),
 * or a nested combination of words and redirections (wc -c < file.in > file.out)
 *  
 *	<command>		::=		<word_list>
 *					|		<redirection>
 *					|		<redirection_list> # Add later
**/

t_astree	*parse_command(t_data *data)
{
	t_astree	*word_list;
	t_astree	*redirection;
	t_token		*token_backup;

	token_backup = data->token_ptr;
	redirection = parse_redirection(data);
	if (redirection)
		return (redirection);
	data->token_ptr = token_backup;
	word_list = parse_word_list(data);
	if (word_list)
		return (word_list);
	return (NULL);
}
