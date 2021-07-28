#include "minishell.h"
#include "environ.h"
#include "libft.h"

void	increment_shlvl(t_environ *env)
{
	char	*shlvl_str;
	int		shlvl_nb;

	shlvl_str = environ_get(env, "SHLVL");
	shlvl_nb = ft_atoi(shlvl_str);
	shlvl_nb++;
	environ_set(env, "SHLVL", ft_itoa(shlvl_nb));
}
