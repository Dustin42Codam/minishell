#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>

/*
**	COLORS THAT YOU SEE ON THE PROOMPT
*/

# define BGRN "\033[32;1;4m"
# define BBLU "\033[34;1;4m"
# define WHT "\033[97;0;4m"
# define END "\033[0m"

/**
 * Main struct for storing all sort of data.
 * We can store everything we want and just
 * pass different members down to functions
 * if we need to.
 * */
typedef struct s_data
{
	size_t	line_len;
	char	**env;
	char	*line;
}	t_data;

t_data		*init_data(char **envp);
void		free_data(t_data *data);
void		exit_shell(int error_id);
size_t		read_line(char **line);

#endif
