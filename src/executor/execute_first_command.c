/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_first_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:24 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/16 19:24:32 by dkrecisz      ########   odam.nl         */
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

int	execute_first_command(t_data *data, t_astree *node, t_file_io fd)
{
	if (node == NULL)
		return 1;
	else if (is_redirection(node->type))
		execute_redirection(data, node, &fd);
	else if (node->type & AST_HERE_DOC)
		execute_here_doc(data, node, fd);
	else if (node->type == AST_WORD)
		execute_word_list(data, node, fd);
	data->error = 0;
	return (1);
}
