#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define BUILTIN_ECHO	1
# define BUILTIN_CD		2
# define BUILTIN_PWD	3
# define BUILTIN_EXPORT	4
# define BUILTIN_UNSET	5
# define BUILTIN_ENV	6
# define BUILTIN_EXIT	7

int	builtin_echo(t_command *cmd);
int	builtin_cd(t_command *cmd, t_environ *env);
int	builtin_pwd(t_command *cmd);
int	builtin_export(t_command *cmd, t_environ *env);
int	builtin_unset(t_command *cmd, t_environ *env);
int	builtin_env(t_command *cmd, t_environ *env);
int	builtin_exit(t_command *cmd);

#endif
