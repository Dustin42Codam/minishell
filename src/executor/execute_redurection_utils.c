/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redurection_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts <alkrust@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 11:55:19 by alkrusts      #+#    #+#                 */
/*   Updated: 2021/10/13 11:57:44 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

#include <fcntl.h>

void	create_file(t_astree *node, t_file_io *fd)
{
	if (node->type & AST_REDIR_OUT)
		fd->output = open(node->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (node->type & AST_APPEND)
		fd->output = open(node->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
}
