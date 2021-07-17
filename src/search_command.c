#include "minishell.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include 	<stdio.h>
#include 	<stdlib.h>

char	*get_try_path(char *file, char *path)
{
	char	*try_path;
	size_t	len;

	len = ft_strlen(file) + ft_strlen(path) + 1;
	try_path = (char *)secure_calloc(len + 1, sizeof(char));
	ft_strlcpy(try_path, path, len);
	ft_strlcat(try_path, "/", len);
	ft_strlcat(try_path, file, len + 1);
	return (try_path);
}

void	search_command(t_astree *node)
{
	struct stat	statbuf;
	char		**path;
	char		*try_path;
	int			i;

	if (ft_strchr(node->str, '/'))
		return ;
	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		try_path = get_try_path(node->str, path[i]);
		if (stat(try_path, &statbuf) == 0)
		{
			free(node->str);
			node->str = try_path;
			errno = 0;
			return ;
		}
		free(try_path);
		i++;
	}
}
