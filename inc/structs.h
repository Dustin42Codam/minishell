#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

/**
 * s_astree - Struct for abstract syntax tree nodes
 * An AST holds the order of command execution.
 * Root and interior nodes consist of operators.
 * Leaf nodes represent commands.
 * Member description:
 * @left:			Pointer to left neighbour node.
 * @right:			Pointer to right neighbour node. 
 * @str:			String representing a command, argument, path or operator. 
 * @type:			Value for identifying the node type. 
 * */
typedef struct s_astree
{
	struct s_astree	*left;
	struct s_astree	*right;
	char			*str;
	int				type;
}	t_astree;

/**
 * s_token - Struct for a linked list of tokens.
 * Member description:
 * @type:			Value for token type identification. See token macros above.
 * @str:			Token string which holds a path, command, argument or operator.
 * @next:			Pointer to the address of the next token.
 * */
typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

/**
 * s_command - Struct for building a command
 * Member description:
 * @argv:			List of a command and its arguments.
 * @argc:			The total amount of arguments.
 * */
typedef struct s_command
{
	char	**argv;
	int		argc;
}	t_command;

/**
 * s_expansion - Struct for expanding environment variables
 * Member description:
 * @substrings:		Linked list of substrings that form the new expanded string
 * @merged_string:	The resulting merged string of all substrings.
 * @var_key:		The name of the environment variable to expand
 * @var_value:		Value of an environment variable.
 * @copy_start:		Index position of the next substring to copy.
 * @i:				Iterator variable.
 * */
typedef struct s_expansion
{
	t_list	*substrings;
	char	*merged_string;
	char	*var_key;
	char	*var_value;
	size_t	copy_start;
	size_t	i;
}	t_expansion;

/**
 * s_data - Main struct for storing all sort of data.
 * Member description:
 * @env:			a copy of the environment variable list.
 * @line:			raw input string.
 * @line_len:		length of raw input string.
 * @token:			head of linked list of tokens.
 * @token_ptr:		temp node in token list.
 * @astree:			pointer to root node of the AST.
 * @error:			variable for specific error handling.
 * @token_mask:		bit mask of all token types in the line.
 * */
typedef struct s_data
{
	char		**env;
	char		*line;
	size_t		line_len;
	t_token		*token;
	t_token		*token_ptr;
	t_astree	*astree;
	int			error;
	int			token_mask;
}	t_data;

#endif
