#include "minishell.h"
#include "libft.h"
#include <errno.h>

void	*minishell_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		exit_minishell(errno);
	return (ptr);
}
