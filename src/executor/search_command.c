/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:43 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:57:58 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "environ.h"
#include "builtins.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

static char	*get_try_path(char *file, char *path)
{
	char	*try_path;
	size_t	len;

	len = ft_strlen(file) + ft_strlen(path) + 1;
	try_path = (char *)minishell_calloc(len + 1, sizeof(char));
	ft_strlcpy(try_path, path, len);
	ft_strlcat(try_path, "/", len);
	ft_strlcat(try_path, file, len + 1);
	return (try_path);
}

static int	check_if_builtin(char *s)
{
	if (ft_strncmp("echo", s, 5) == 0)
		return (BUILTIN_ECHO);
	else if (ft_strncmp("cd", s, 3) == 0)
		return (BUILTIN_CD);
	else if (ft_strncmp("pwd", s, 4) == 0)
		return (BUILTIN_PWD);
	else if (ft_strncmp("export", s, 7) == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strncmp("unset", s, 6) == 0)
		return (BUILTIN_UNSET);
	else if (ft_strncmp("env", s, 4) == 0)
		return (BUILTIN_ENV);
	else if (ft_strncmp("exit", s, 5) == 0)
		return (BUILTIN_EXIT);
	return (0);
}

static void	free_path(char **path)
{
	size_t	i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

static int	do_path(char **path, t_astree *node)
{
	char		*try_path;
	struct stat	statbuf;
	int			i;

	i = 0;
	while (path && path[i])
	{
		try_path = get_try_path(node->str, path[i]);
		if (stat(try_path, &statbuf) == 0)
		{
			free(node->str);
			node->str = try_path;
			errno = 0;
			free_path(path);
			return (0);
		}
		free(try_path);
		i++;
	}
	return (1);
}

int	search_command(t_astree *node, t_environ *env)
{
	char		**path;
	int			builtin_id;

	builtin_id = check_if_builtin(node->str);
	if (ft_strchr(node->str, '/') || builtin_id)
		return (builtin_id);
	path = ft_split(environ_get(env, "PATH"), ':');
	if (do_path(path, node) == 0)
		return (0);
	free_path(path);
	return (0);
}
