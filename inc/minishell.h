#ifndef MINISHELL_H
# define MINISHELL_H

/*
**	COLORS THAT YOU SEE ON THE PROOMPT
*/

# define BGRN "\033[32;1;4m"
# define BBLU "\033[34;1;4m"
# define WHT "\033[97;0;4m"
# define END "\033[0m"

# include <unistd.h>

# define EMPTY 0
# define WORD 1
# define SQUOTE 2
# define DQUOTE 4
# define SEMICOLON 8
# define PIPE 16
# define REDIR_IN 32
# define REDIR_OUT 64


# define AST_PIPE		1		//	<command> '|' <job>
# define AST_LIST		2		//	<job> ';' <command line>
# define AST_REDIR_IN	4		//	<simple command> '<' <filename>
# define AST_REDIR_OUT	8		//	<simple command> '>' <filename>
# define AST_CMD		16		//	<pathname> <token list>	// S_CMD means simple command
# define AST_CMD_ARG	32		//	<token> <token list>	// CMD_ARGV means argument vector for a command
# define AST_TOKEN		64		//	<token>

/**
 * Linked list for storing information about tokens.
 * */
typedef struct s_token
{
	int				id;
	char			*str;
	struct s_token	*next;
}	t_token;

/**
 * Abstract syntax tree which
 * holds the order of command execution.
 * Root and interior nodes consist of operators
 * and leaf nodes represent commands.
 * */
typedef struct s_astree
{
	struct s_astree	*left;
	struct s_astree	*right;
	char			*str;
	int				type;
}	t_astree;

typedef struct s_command
{
	char	**argv;
	int		argc;
}	t_command;

/**
 * Main struct for storing all sort of data.
 * We can store everything we want and just
 * pass different members down to functions
 * if we need to.
 * 
 * Member description:
 * @env:			copy of the environment variable list
 * @line:			raw input string
 * @line_len:		length of line
 * @token:			linked list of tokens
 * @token_ptr:		a pointer to a token
 * @astree:			root of abstract syntax tree
 * @syntax_table:	perhaps add a syntax table for faster type lookup
 * */
typedef struct s_data
{
	char		**env;
	char		*line;
	size_t		line_len;
	t_token		*token;
	t_token		*token_ptr;
	// t_token		*save_token;
	t_astree	*astree;
	// char		syntax_table[256];
}	t_data;

ssize_t		read_line(char **line);
void		exit_shell(int error_id);
int			call(char *line);

t_data		*init_data(char **envp);
void		free_data(t_data *data);

/*
**	LEXER - TOKENIZER
*/
int			tokenizer(t_data **data, char *line);
void		init_next_token(t_token **token, size_t len, size_t i);
int			token_meta(t_token **token, t_data **data, size_t *i, char c);
int			token_quote(t_token **token, t_data **data, size_t *i, char c);
int			get_token_id(char c);
void		free_token_list(t_token *token);
t_token		*init_token_list(size_t len);

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

#endif
