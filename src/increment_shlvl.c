#include "minishell.h"
#include "environ.h"
#include "libft.h"
#include <errno.h>

void	increment_shlvl(t_environ *env)
{
	t_environ	*new;
	char		*shlvl_str;
	char		*shlvl_str_new;
	char		*key_value;
	int			shlvl_nb;

	shlvl_str = environ_get(env, "SHLVL");
	shlvl_nb = ft_atoi(shlvl_str);
	shlvl_nb++;
	shlvl_str_new = ft_itoa(shlvl_nb);
	key_value = ft_strjoin("SHLVL=", shlvl_str_new);
	if (errno)
		exit_minishell(errno);
	new = environ_new(key_value);
	environ_add_back(&env, new);
}
