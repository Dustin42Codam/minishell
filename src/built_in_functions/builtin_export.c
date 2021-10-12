/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:54:51 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:58:23 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

static void	add_new_variable(t_environ *env, t_environ *new)
{
	environ_modify(env, new->key, new->value);
	free(new->key);
	free(new->value);
	free(new->key_value);
	free(new);
}

int	builtin_export(t_command *cmd, t_environ *env)
{
	t_environ	*new;
	size_t		i;
	int			exit_status;

	if (cmd->argc == 1)
		return (print_exported_variables(cmd, env));
	i = 1;
	exit_status = 0;
	while (cmd->argv[i])
	{
		if (check_variable_name(cmd->argv[i]))
			exit_status = export_error(cmd->argv[i]);
		else
		{
			new = environ_new(cmd->argv[i]);
			if (environ_get(env, new->key))
				add_new_variable(env, new);
			else
				environ_add_back(&env, new);
		}
		i++;
	}
	return (exit_status);
}
