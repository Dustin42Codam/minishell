#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

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
 * s_token - Struct for a linked list of tokens.
 * Member description:
 * @type:			Value for token type identification.
 * @str:			Token string for a path, command, argument or operator.
 * @start:			Index where the token starts inside the input line.
 * @end:			Index of the last token character inside the input line.
 * @next:			Pointer to the address of the next token.
 * */
typedef struct s_token
{
	int				type;
	char			*str;
	size_t			start;
	size_t			end;
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
 * s_environ - Linked list for environment variables
 * Member description:
 * @key:			Name (or key) of a variable.
 * @value:			Value of a variable.
 * @key_value:		Key=value pair in one string.
 * @next:			Pointer to next node.
 * */
typedef struct s_environ
{
	char				*key;
	char				*value;
	char				*key_value;
	struct s_environ	*next;
}	t_environ;

/**
 * s_file_io - File descriptors for input/output redirection
 * Member description:
 * @pipe:			Pipe array.
 * 					pipe[0]	-	pipe read fd
 * 					pipe[1]	-	pipe write fd
 * @read:			Read from this file descriptor.
 * @write:			Write into this file descriptor.
 * @dup_stdin:		Is set to 1 if STDIN needs to be duplicated, otherwise 0.
 * @dup_stdout:		Is set to 1 if STDOUT needs to be duplicated, otherwise 0.
 * @save_stdin:		A duplicate of STDIN.
 * @save_stdout:	A duplicate of STDOUT.
 * @input:	File descriptor referencing an input file.
 * @output:	File descriptor referencing an output file.
 * */
typedef struct s_file_io
{
	int		pipe[2];
	int		read;
	int		write;
	int		dup_stdin;
	int		dup_stdout;
	int		save_stdin;
	int		save_stdout;
	int		output;
	int		input;
}	t_file_io;

/**
 * s_command - Struct for building a command
 * Member description:
 * @argv:			List of a command and its arguments.
 * @argc:			The total amount of arguments.
 * @builtin_id:		Unique value telling if command is a builtin.
 * 					0 if command is not a builtin.
 * @exit_status:	Exit code of the previous command.
 * @fd:				File descriptors for pipes and redirections.
 * @env:			A reference to the linked list of environment variables.
 * */
typedef struct s_command
{
	char		**argv;
	int			argc;
	int			builtin_id;
	int			exit_status;
	t_file_io	fd;
	t_environ	*env;
}	t_command;

/**
 * s_data - Main struct for storing all sort of data.
 * Member description:
 * @env:			a copy of the environment variable list.
 * @line:			raw command line.
 * @line_len:		length of command line.
 * @token:			head of linked list of tokens.
 * @token_ptr:		temporary node in token list.
 * @astree:			pointer to root node of the abstract syntax tree.
 * @error:			variable for specific error handling.
 * @token_mask:		bit mask of all token types in the line.
 * @interactive:	Value is set to TRUE=1 if shell is in interactive mode
 * 					and FALSE=0 if the shell is non-interactive.
 * @exit_status:	exit code of last executed command in the pipeline.
 * @sig_NO:			signal number read by ft_readline
 * @prompt:			prompt settings
 * @new_term:		new termios settings - minishell exclusive
 * @old_term:		old default termios settings
 * */
typedef struct s_data
{
	t_environ		*env;
	char			*line;
	size_t			line_len;
	t_token			*token;
	t_token			*token_ptr;
	t_astree		*astree;
	int				error;
	int				token_mask;
	int				interactive;
	int				exit_status;
	int				sig_NO;	// delete?
}	t_data;

#endif
