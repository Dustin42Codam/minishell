/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:04 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:58:19 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include <errno.h>
#include <stdlib.h>

void	environ_add_back(t_environ **env, t_environ *new)
{
	t_environ	*tmp;

	tmp = *env;
	if (new == NULL)
		return ;
	if (*env == NULL)
		*env = new;
	else
	{
		while (tmp->next)
		{
			if (environ_compare(new->key, tmp->key))
			{
				free(tmp->value);
				free(tmp->key_value);
				tmp->value = new->value;
				tmp->key_value = new->key_value;
				free(new->key);
				free(new);
				return ;
			}
			tmp = tmp->next;
		}
		tmp->next = new;
	}
}

t_environ	*environ_new(const char *key_value)
{
	t_environ	*new;
	size_t		key_len;
	size_t		key_value_len;

	if (!key_value || key_value[0] == 0 || ft_strchr(key_value, '=') == NULL)
		return (NULL);
	key_value_len = ft_strlen(key_value);
	new = (t_environ *)minishell_calloc(1, sizeof(t_environ));
	new->key = (char *)minishell_calloc(key_value_len + 1, sizeof(char));
	new->value = (char *)minishell_calloc(key_value_len + 1, sizeof(char));
	new->key_value = ft_strdup(key_value);
	if (new->key_value == NULL)
		exit_minishell(errno);
	key_len = ft_strchr(key_value, '=') - key_value;
	ft_strlcpy(new->key, key_value, key_len + 1);
	ft_strlcpy(new->value, key_value + key_len + 1, key_value_len);
	return (new);
}

t_environ	*environ_deep_copy(char **env)
{
	t_environ	*head;
	size_t		i;

	i = 0;
	head = NULL;
	if (env == NULL || *env == NULL)
		return (NULL);
	while (env[i])
	{
		environ_add_back(&head, environ_new(env[i]));
		i++;
	}
	return (head);
}

void	environ_modify(t_environ *head, char *key, char *value)
{
	t_environ	*tmp;

	tmp = head;
	while (head && tmp && key)
	{
		if (environ_compare(tmp->key, key))
		{
			free(tmp->value);
			free(tmp->key_value);
			if (value == NULL)
				tmp->value = ft_strdup("");
			else
				tmp->value = ft_strdup(value);
			if (tmp->value == NULL)
				exit_minishell(errno);
			tmp->key_value = environ_get_keyvalue(key, value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	environ_set(t_environ *head, char *key, char *value)
{
	t_environ	*new;

	if (key == NULL || key[0] == 0)
		return ;
	if (environ_get(head, key))
	{
		environ_modify(head, key, value);
		return ;
	}
	new = (t_environ *)minishell_calloc(1, sizeof(t_environ));
	new->key = ft_strdup(key);
	if (new->key == NULL)
		exit_minishell(errno);
	if (value == NULL)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(value);
	if (new->value == NULL)
		exit_minishell(errno);
	environ_add_back(&head, new);
}
