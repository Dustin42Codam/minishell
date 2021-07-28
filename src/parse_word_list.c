#include "minishell.h"
#include "parser.h"
#include "lexer.h"

/**
 *	<word list>		::=	<word>
 *					|	<word> <word list>
**/
t_astree	*parse_word_list(t_data *data)
{
	t_astree	*child_node;
	t_astree	*parent_node;
	t_token		*token_backup;
	char		*word_string;

	token_backup = data->token_ptr;
	if (get_next_token(data, &word_string, WORD))
	{
		data->token_ptr = token_backup;
		return (NULL);
	}
	child_node = parse_word_list(data);
	parent_node = (t_astree *)secure_calloc(1, sizeof(t_astree));
	init_ast_node(parent_node, word_string, AST_WORD);
	insert_ast_node(parent_node, NULL, child_node);
	return (parent_node);
}
