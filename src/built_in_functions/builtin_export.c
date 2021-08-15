#include "minishell.h"
#include "libft.h"
#include "environ.h"
#include <stdlib.h>

static int	check_variable_name(char *name)
{
	int	letter;

	letter = 0;
	if (name == NULL || name[0] == 0 || name[0] == '=')
		return (EXIT_FAILURE);
	while (*name && *name != '=')
	{
		if (ft_isalpha(*name))
			letter = TRUE;
		else if (ft_isalnum(*name) == 0 && *name != '_')
			return (EXIT_FAILURE);
		else if (ft_isdigit(*name) && letter == 0)
			return (EXIT_FAILURE);
		name++;
	}
	return (EXIT_SUCCESS);
}

static int	print_exported_variables(t_command *cmd, t_environ	*env)
{
	while (env)
	{
		minishell_putstr_fd("declare -x ", cmd->fd.write);
		minishell_putstr_fd(env->key, cmd->fd.write);
		minishell_putstr_fd("=\"", cmd->fd.write);
		minishell_putstr_fd(env->value, cmd->fd.write);
		minishell_putendl_fd("\"", cmd->fd.write);
		env = env->next;
	}
	return (0);
}

static int	export_error(char *arg)
{
	minishell_putstr_fd("minishell: export: `", 2);
	minishell_putstr_fd(arg, 2);
	minishell_putendl_fd("\': not a valid identifier", 2);
	return (1);
}

int	builtin_export(t_command *cmd, t_environ *env)
{
	size_t	i;
	int		error;

	if (cmd->argc == 1)
		return (print_exported_variables(cmd, env));
	i = 1;
	error = 0;
	while (cmd->argv[i])
	{
		if (check_variable_name(cmd->argv[i]))
			error = export_error(cmd->argv[i]);
		else
			environ_add_back(&env, environ_new(cmd->argv[i]));
		i++;
	}
	return (error);
}
