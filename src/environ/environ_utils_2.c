/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:04 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/11/01 11:13:39 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

void	environ_modify_prep(t_environ **head, char *key, char *value)
{
	t_environ	*new;

	new = minishell_calloc(1, sizeof(t_environ));
	new->key = key;
	new->value = value;
	new->key_value = environ_get_keyvalue(key, value);
	environ_modify(head, new);
}
