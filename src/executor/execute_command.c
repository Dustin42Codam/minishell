/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:24 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/18 09:39:33 by dkrecisz      ########   odam.nl         */
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

void	execute_command(t_data *data, t_astree *node)
{
	if (node == NULL)
		return ;
	else if (is_redirection(node->type))
		execute_redirection(data, node, data->fd);
	else if (node->type & AST_HERE_DOC)
		execute_here_doc(data, node, data->fd);
	else if (node->type == AST_WORD)
		execute_word_list(data, node);
	data->error = 0;
	data->fd->input = 0;
	data->fd->output = 0;
}
