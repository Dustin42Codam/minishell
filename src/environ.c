#include "minishell.h"
#include "environ.h"
#include <errno.h>
#include <stdlib.h>

static void	environ_add_back(t_environ **env, t_environ *new)
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
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_environ	*environ_new(const char *key_value)
{
	t_environ	*new;
	size_t		key_len;

	if (!key_value || key_value[0] == 0 || ft_strchr(key_value, '=') == NULL)
		return (NULL);
	new = (t_environ *)secure_calloc(1, sizeof(t_environ));
	new->key = (char *)secure_calloc(ft_strlen(key_value) + 1, sizeof(char));
	new->value = (char *)secure_calloc(ft_strlen(key_value) + 1, sizeof(char));
	new->key_value = ft_strdup(key_value);
	if (new->key_value == NULL)
		exit_shell(errno);
	key_len = ft_strchr(key_value, '=') - key_value;
	ft_strlcpy(new->key, key_value, key_len + 1);
	ft_strlcpy(new->value, key_value + key_len + 1, ft_strlen(key_value));
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

static void	environ_modify(t_environ *head, char *key, char *value)
{
	t_environ	*tmp;

	tmp = head;
	while (head && tmp && key)
	{
		if (environ_compare(tmp->key, key))
		{
			free(tmp->value);
			if (value == NULL)
				tmp->value = ft_strdup("");
			else
				tmp->value = ft_strdup(value);
			if (tmp->value == NULL)
				exit_shell(errno);
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
	new = (t_environ *)secure_calloc(1, sizeof(t_environ));
	new->key = ft_strdup(key);
	if (new->key == NULL)
		exit_shell(errno);
	if (value == NULL)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(value);
	if (new->value == NULL)
		exit_shell(errno);
	environ_add_back(&head, new);
}
