/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:55:04 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/28 14:42:14 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"

void	environ_modify_prep(t_environ *head, char *key, char *value)
{
	t_environ	*new;

	new = (t_environ *)minishell_calloc(1, sizeof(t_environ));
	new->key = key;
	new->value = value;
	new->key_value = NULL;
	environ_modify(head, new);
}
