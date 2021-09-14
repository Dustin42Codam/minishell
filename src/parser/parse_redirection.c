/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirection.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:56:47 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:57:48 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (ast_node_type & AST_HERE_DOC && data->token_ptr->type & RMQUOTE)
		ast_node_type |= RMQUOTE;
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

/**
 * parse_redirection_list - creates a AST node for <redirection_list>
 * 
 *	<redirection_list>	::= <redirection>
 *						|	<redirection_list> <redirection>
**/

t_astree	*parse_redirection_list(t_data *data)
{
	t_astree	*redirection_list;
	t_astree	*redirection;
	t_astree	*word_list;
	char		*filename;
	int			ast_node_type;
	t_token		*token_backup;

	token_backup = data->token_ptr;
	word_list = parse_word_list(data);
	ast_node_type = get_ast_node_type(data->token_ptr->type);
	if (get_next_token(data, NULL, (HERE_DOC | REDIR_IN | APPEND | REDIR_OUT)))
	{
		data->token_ptr = token_backup;
		delete_ast(word_list);
		return (NULL);
	}
	if (ast_node_type & AST_HERE_DOC && data->token_ptr->type & RMQUOTE)
		ast_node_type |= RMQUOTE;
	if (get_next_token(data, &filename, WORD))
	{
		data->token_ptr = token_backup;
		delete_ast(word_list);
		return (NULL);
	}
	if (word_list == NULL)
		word_list = parse_word_list(data);
	redirection = parse_redirection_list(data);
	redirection_list = (t_astree *)minishell_calloc(1, sizeof(t_astree));
	init_ast_node(redirection_list, filename, ast_node_type);
	insert_ast_node(redirection_list, redirection, word_list);
	return (redirection_list);
}
