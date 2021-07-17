#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

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

size_t		read_line(char **line);
void		exit_shell(int error_id);

t_data		*init_data(char **envp);
void		free_data(t_data *data);

/*
**	MISC - HELPER FUNCTIONS
*/
void		*secure_calloc(size_t nmemb, size_t size);

#endif
