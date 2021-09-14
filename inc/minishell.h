#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_sig;

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

void	minishell_non_interactive(t_data *data, int argc, char *argv[]);
void	minishell_interactive(t_data *data);
void	exit_minishell(int error_id);
void	exit_minishell_custom(char *str);
t_data	*init_data(char **envp);
void	free_data(t_data *data);
void	increment_shlvl(t_environ *env);
void	quote_removal(t_data **data);
void	minishell_putstr(const char *str);

/**
 * Libft and glibc wrapper functions 
 * */

void	*minishell_calloc(size_t nmemb, size_t size);
ssize_t	minishell_write(int fd, const void *buf, size_t count);
ssize_t	minishell_putchar_fd(const char c, int fd);
ssize_t	minishell_putstr_fd(const char *s, int fd);
ssize_t	minishell_putendl_fd(const char *s, int fd);

/*
**	SIGNAL HOOK FUNCTIOMS
*/

void	print_pr(int ig);
void	sig_quit(int ig);
void	decrement_global_sig(void);
void	incrment_global_sig(void);

#endif
