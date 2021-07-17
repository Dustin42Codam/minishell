#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

void	*secure_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		exit_shell(errno);
	return (ptr);
}
