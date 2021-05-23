#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "libft.h"
#include "minishell.h"

t_built_in	*init(void)
{
	t_built_in	*new;

	new = malloc(sizeof(t_built_in) * 1);
	if (errno)
		exit(!!printf("Error\nOut of mem init.c:5\n"));
	new->functions[0] = ft_strdup("echo");
	new->functions[1] = ft_strdup("cd");
	new->functions[2] = ft_strdup("pwd");
	new->functions[3] = ft_strdup("export");
	new->functions[4] = ft_strdup("unset");
	new->functions[5] = ft_strdup("env");
	new->functions[6] = ft_strdup("exit");
	if (errno)
		exit(!!printf("Error\nOut of mem init.c:ft_strdup.c\n"));
	return (new);
}
