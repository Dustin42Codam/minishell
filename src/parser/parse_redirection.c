#include "minishell.h"
#include "parser.h"
#include "lexer.h"

/**
 * parse_redirection - creates a AST node for <redirection>
 * 
 *	<redirection>	::=	'<' <filename> <word_list>	# redir_in
 *					|	<word_list> '<' <filename>
 *					|	'<' <filename> 
 *					|
 *					|	'>' <filename> <word_list>	# redir_out
 *					|	<word_list> '>' <filename>
 *					|	'>' <filename>
 *					|
 *					|	'>>' <filename> <word_list>	# append
 *					|	<word_list> '>>' <filename>
 *					|	'>>' <filename>
 *					|
 *					|	'<<' <filename> <word_list>	# here_docs
 *					|	<word_list> '<<' <filename>
 *					|	'<<' <filename>
 *					|	
 *					|	# ???
 *					|	<word_list> '<>' <word_list>	# wtf?!
 *					|	'<>' <word_list>
 *					|	'>|' <word_list>
 *					|	<word_list> '>|' <word_list>
**/

t_astree	*parse_redirection(t_data *data)
{
	t_astree	*redirection;
	t_astree	*word_list;
	char		*filename;
	int			ast_node_type;

	word_list = parse_word_list(data);
	ast_node_type = get_ast_node_type(data->token_ptr->type);
	if (get_next_token(data, NULL, (HERE_DOC | REDIR_IN | APPEND | REDIR_OUT)))
	{
		delete_ast(word_list);
		return (NULL);
	}
	if (get_next_token(data, &filename, WORD))
	{
		delete_ast(word_list);
		return (NULL);
	}
	if (word_list == NULL)
		word_list = parse_word_list(data);
	redirection = (t_astree *)minishell_calloc(1, sizeof(t_astree));
	init_ast_node(redirection, filename, ast_node_type);
	insert_ast_node(redirection, NULL, word_list);
	return (redirection);
}
