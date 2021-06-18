#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

/**
 *	Boolean defines - Because we are too cool for stdbool.
**/
# define FALSE	0
# define TRUE	1

/*
**	COLORS THAT YOU SEE ON THE PROOMPT
*/
# define BGRN "\033[32;1;4m"
# define BBLU "\033[34;1;4m"
# define WHT "\033[97;0;4m"
# define END "\033[0m"

/**
 *	Strings used by the lexical analyzer
**/
# define META_CHAR "<>;|"
# define BREAK_CHAR "<>;| \t\n"
# define QUOTE_CHAR "\"\'"
# define EXP_CHAR "$"
# define BSDQUOTE_CHAR "\n\"$\\`"
# define SPECIAL_VAR_CHAR "?"
# define BLANK_CHAR "\t "
# define ESCAPE_CHAR "\\"
# define END_CHAR "\n\0"

/**
 * Token type macros
**/
# define EMPTY		0x0000
# define WORD		0x0001
# define SEMICOLON	0x0002
# define PIPE		0x0004
# define REDIR_IN	0x0008
# define REDIR_OUT	0x0010
# define APPEND		0x0020
# define EXPAND		0x0040
# define SQUOTE		0x0080
# define DQUOTE		0x0100

/**
 * Abstract syntax tree node macros
**/
# define AST_PIPE		0x0001		//	<command> '|' <job>
# define AST_LIST		0x0002		//	<job> ';' <command line>
# define AST_REDIR_IN	0x0004		//	<simple command> '<' <filename>
# define AST_REDIR_OUT	0x0008		//	<simple command> '>' <filename>
# define AST_CMD		0x0010		//	<pathname> <token list>	// S_CMD means simple command
# define AST_CMD_ARG	0x0020		//	<token> <token list>	// CMD_ARGV means argument vector for a command
# define AST_TOKEN		0x0040		//	<token>

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
 * s_data - Main struct for storing all sort of data.
 * Member description:
 * @env:			copy of the environment variable list
 * @line:			raw input string
 * @line_len:		length of line
 * @token:			root pointer to the linked list of tokens
 * @token_ptr:		pointer used for traversing the linked list of tokens.
 * @astree:			root pointer to the abstract syntax tree.
 * @error:			variable for specific error handling.
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
}	t_data;

size_t		read_line(char **line);
void		exit_shell(int error_id);

t_data		*init_data(char **envp);
void		free_data(t_data *data);

/*
**	LEXER - TOKENIZER
*/
int			tokenizer(t_data **data, char *line);
t_token		*init_token_list(size_t len);
void		init_new_token(t_token **token, size_t len, size_t *j);
void		free_token_list(t_token *token);
void		make_token_meta(t_token **token, t_data **data, size_t *i, size_t *j);
void		make_token_quote(t_token **token, t_data **data, size_t *i, size_t *j);
int			get_token_type(char *s);

char		*is_meta(char c);
char		*is_break(char c);
char		*is_quote(char c);
char		*is_expansion(char c);
char		*is_bsdquote(char c);
char		*is_escape(char c);
char		*is_special_var(char c);
char		*is_blank(char c);
char		*is_end(char c);

void		print_token_types(t_token *token);

/*
**	PARSER - ABSTRACT SYNTAX TREE
*/

void		parse_astree(t_data *data);

void		init_ast_node(t_astree *node, char *arg, int type);
void		insert_ast_node(t_astree *node, t_astree *left, t_astree *right);
void		delete_ast(t_astree *node);

t_astree	*parse_command_line(t_data *data);
t_astree	*parse_cmd_line_semi(t_data *data);
t_astree	*parse_cmd_line_sequence(t_data *data);

t_astree	*parse_job(t_data *data);
t_astree	*parse_job_pipeline(t_data *data);

t_astree	*parse_command(t_data *data);
t_astree	*parse_command_redir_out(t_data *data);
t_astree	*parse_command_redir_in(t_data *data);

t_astree	*parse_simple_command(t_data *data);
t_astree	*parse_token_list(t_data *data);
t_astree	*parse_tokens(t_data *data);
int			get_next_token(t_data *data, char **token_str, int token_type);

/*
**	EXECUTOR
*/
void		execute(t_data *data);
void		execute_command_line(t_data *data);
void		execute_job(t_data *data);
void		execute_command(t_data *data);
void		execute_simple_command(t_data *data);

void		make_command_argv(t_astree *node, t_command *cmd);
void		execute_command_argv(t_command *cmd, char **env);
void		free_command_argv(t_command *cmd);

#endif
