#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void	execute(t_data *data);
void	execute_pipeline(t_data *data, t_file_io fd);
void	execute_command(t_data *data, t_astree *node, t_file_io fd);
void	execute_here_doc(t_data *data, t_astree *node, t_file_io fd);
void	execute_word_list(t_data *data, t_astree *node, t_file_io fd);
void	execute_redirection(t_data *data, t_astree *node, t_file_io *fd);
void	execute_redirection_in(t_data *data, t_astree *node, t_file_io *fd);
void	execute_redirection_out(t_data *data, t_astree *node, t_file_io *fd);
void	execute_builtin(t_data *data, t_command *cmd, t_environ *env);
void	make_command(t_data *data, t_astree *node, t_command *cmd, \
				t_file_io fd);
void	execute_command_argv(t_data *data, t_command *cmd, t_environ *env);
int		search_command(t_astree *node, t_environ *env);
void	print_error(t_data *data, char *str, int error_id);

#endif
