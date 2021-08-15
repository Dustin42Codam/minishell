#include "minishell.h"
#include "libft.h" 

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

static char	*get_path(void)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char), PATH_MAX);
	if (is_string_NULL(cwd) == true)
		exit_minishell(errno);
	if (getcwd(cwd, PATH_MAX) == NULL)
		exit_minishell(errno);
	return (cwd);
}

char	*get_prompt_message(void)
{
	char	*message;
	char	*last_folder;
	char	*cwd;

	cwd = get_path();
	last_folder = ft_strrchr(cwd, '/');
	message = ft_strjoin(last_folder, "$");
	if (is_string_NULL(message) == true)
		exit_minishell(errno);
	free(cwd);
	return (message);
}
