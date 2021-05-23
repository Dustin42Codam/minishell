#include "minishell.h"
#include "libft.h"

int	is_builtin(char *test)
{
	t_built_in	built_in;
	int		index;

	index = 0;
	while (built_in.functions[index])
	{
		if (ft_strnstr(test, built_in.functions[index],
			ft_strlen(test)))
			return (1);
		index++;
	}
	return (0);
}
