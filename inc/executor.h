#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void		execute(t_data *data);

void		execute_pipeline(t_data *data);
void		execute_command(t_data *data);
int			execute_builtin(t_command *cmd, t_environ *env);

void		make_command_argv(t_data *data, t_astree *node, t_command *cmd);
int			execute_command_argv(t_command *cmd, t_environ *env);
void		free_command_argv(t_command *cmd);

void		expand_variables(t_data *data);
int			search_command(t_astree *node, t_environ *env);

#endif
