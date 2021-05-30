#include "minishell.h"
#include "libft.h"
#include <errno.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (errno)
		exit_shell(errno);
	return (data);
}
