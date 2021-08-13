#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define ECHO	1
# define CD		2
# define PWD	3
# define EXPORT	4
# define UNSET	5
# define ENV	6
# define EXIT	7

int	builtin_echo(t_command *cmd);
int	builtin_cd(t_command *cmd, t_environ *env);
int	builtin_pwd(t_command *cmd);
int	builtin_export(t_command *cmd, t_environ *env);
int	builtin_unset(t_command *cmd, t_environ *env);
int	builtin_env(t_command *cmd, t_environ *env);
int	builtin_exit(t_command *cmd);

#endif
