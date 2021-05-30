#ifndef MINISHELL_H
# define MINISHELL_H

/*
**	COLORS THAT YOU SEE ON THE PROOMPT
*/

# define BGRN "\033[32;1;4m"
# define BBLU "\033[34;1;4m"
# define WHT "\033[97;0;4m"
# define END "\033[0m"

# include <stddef.h>

# define TOKEN -1
# define WORD 0
# define SQUOTE 1
# define DQUOTE 2
# define SEMICOLON 3
# define PIPE 4
# define REDIR 5

typedef struct s_built_in
{
	char	*functions[7];
}		t_built_in;

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

/**
 * Main struct for storing all sort of data.
 * We can store everything we want and just
 * pass different members down to functions
 * if we need to.
 * */
typedef struct s_data
{
	char		*line;
	size_t		line_len;
	t_token		*token;
	t_astree	*astree;
}	t_data;

void		exit_shell(int error_id);
int			call(char *line);

t_built_in	*init(void);

t_data		*init_data(void);

/*
**	LEXER - TOKENIZER
*/
int			tokenizer(t_data **data, char *line);
int			init_next_token(t_token **token, size_t len, size_t i);
int			token_meta(t_token **token, t_data **data, size_t *i, char c);
int			token_quote(t_token **token, t_data **data, size_t *i, char c);
int			get_token_id(char c);
void		free_token_list(t_token *token);
/*
**	PARSER - ABSTRACT SYNTAX TREE
*/
void		parser(t_data *data);
t_astree	*init_tree(void);


/*
**	BUILT IN FUNCTIONS
*/

int			pwd(void);

#endif
