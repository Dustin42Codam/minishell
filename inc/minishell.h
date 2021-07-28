#ifndef MINISHELL_H
# define MINISHELL_H

# include "terminal_capabilities.h"

# include "structs.h"

/**
 *	Boolean defines - Because we are too cool for stdbool.
**/
# define FALSE	0
# define TRUE	1

/*
**	COLORS THAT YOU SEE ON THE PROOMPT
*/
# define GREEN "\033[32;1;4m"
# define BLUE "\033[34;1;4m"
# define WHITE "\033[97;0;4m"
# define RESET "\033[0m"

void	non_interactive_shell(t_data *data, int argc, char *argv[]);
void	interactive_shell(t_data *data);
size_t	get_size_of_tokens(char **arr);
size_t	read_line(char **line);
void	exit_minishell(int error_id);
void	exit_minishell_custom(char *str);
t_data	*init_data(char **envp);
void	free_data(t_data *data);
void	increment_shlvl(t_environ *env);
void	quote_removal(t_data **data);
void	*minishell_calloc(size_t nmemb, size_t size);

#endif
