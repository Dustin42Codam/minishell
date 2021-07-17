#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <errno.h>

/**
 *	<word list>		::=	<word>
 *					|	<word> <word list>
**/
t_astree	*parse_word_list(t_data *data)
{
	t_astree	*child_token;
	t_astree	*parent_token;
	t_token		*token_backup;
	char		*word_string;

	token_backup = data->token_ptr;
	if (get_next_token(data, &word_string, WORD))
	{
		data->token_ptr = token_backup;
		return (NULL);
	}
	child_token = parse_word_list(data);
	parent_token = (t_astree *)secure_calloc(1, sizeof(t_astree));
	init_ast_node(parent_token, word_string, AST_WORD);
	insert_ast_node(parent_token, NULL, child_token);
	return (parent_token);
}
