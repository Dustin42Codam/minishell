#ifndef MINISHELL_H
# define MINISHELL_H

# define BGRN "\033[32;1;4m"
# define BBLU "\033[34;1;4m"
# define WHT "\033[97;0;4m"

void	exit_shell(int error_id);
char	*read_line(void);

#endif
