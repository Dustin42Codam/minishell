#ifndef MINISHELL_H
# define MINISHELL_H

# define BGRN "\033[32;1;4m"
# define BBLU "\033[34;1;4m"
# define WHT "\033[97;0;4m"
#include "unistd.h"

void	exit_shell(int error_id);
char	*read_line(void);
pid_t	call(char *line);

#endif
