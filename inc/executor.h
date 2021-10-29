/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:54:24 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/28 15:31:21 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void	execute(t_data *data);
void	execute_pipeline(t_data *data);
void	execute_command(t_data *data, t_astree *node);
void	execute_here_doc(t_data *data, t_astree *node, t_file_io *fd);
void	execute_word_list(t_data *data, t_astree *node);
void	execute_redirection(t_data *data, t_astree *node, t_file_io *fd);
void	execute_builtin(t_data *data, t_command *cmd, t_environ *env);
void	make_command(t_data *data, t_astree *node, t_command *cmd);
void	execute_command_argv(t_data *data, t_command *cmd, t_environ *env);
int		execute_first_command(t_data *data, t_astree *node, t_file_io fd);
int		search_command(t_astree *node, t_environ *env);
void	print_error(t_data *data, char *str, int error_id);
void	create_file(t_astree *node, t_file_io *fd);
void	restore_fd(t_file_io *fd);
void	free_child_pid(t_child *head);
void	del_parent(t_exec *stru, t_astree *node);

#endif
