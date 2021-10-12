/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:24 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:58:17 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "parser.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	print_error(t_data *data, char *str, int error_id)
{
	printf("minishell: %s: %s\n", str, strerror(error_id));
	data->exit_status = errno;
	data->error = errno;
	errno = 0;
}

void	execute_command(t_data *data, t_astree *node, t_file_io fd)
{
	if (node == NULL)
		return ;
	else if (is_redirection(node->type))
		execute_redirection(data, node, &fd);
	// else if (node->type & AST_REDIR_IN)
		// execute_redirection_in(data, node, &fd);
	// else if (node->type & (AST_REDIR_OUT | AST_APPEND))
		// execute_redirection_out(data, node, &fd);
	else if (node->type & AST_HERE_DOC)
		execute_here_doc(data, node, fd);
	else if (node->type == AST_WORD)
		execute_word_list(data, node, fd);
	data->error = 0;
}
