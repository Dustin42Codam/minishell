#ifndef MINISHELL_H
# define MINISHELL_H

# define BCYAN "\e[1;36m"
# define RESET "\e[0m"

void	exit_shell(int error_id);
char	*read_line(void);

#endif
