/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:54:54 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:58:22 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int	builtin_pwd(t_command *cmd)
{
	char	cwd[PATH_MAX + 1];

	errno = 0;
	if (cmd->argc > 1 && cmd->argv[1][0] == '-')
	{
		minishell_putendl_fd("minishell: pwd: options are not supported", 2);
		return (2);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (errno);
	minishell_putendl_fd(cwd, cmd->fd.write);
	return (0);
}
