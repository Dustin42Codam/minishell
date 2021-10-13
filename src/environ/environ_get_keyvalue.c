/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_get_keyvalue.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts <alkrust@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:46:58 by alkrusts      #+#    #+#                 */
/*   Updated: 2021/10/13 10:47:06 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environ.h"
#include "libft.h"

#include <errno.h>

/**
 * environ_get_keyvalue - creates a key-value pair in one string
 *  
 * just for a reminder why we need to add '+2' for calculating len:
 * length of key-value pair = length of key + '=' + length of value + '\0'
 * 
 * */
char	*environ_get_keyvalue(char *key, char *value)
{
	char	*keyvalue;
	size_t	len;
	size_t	key_len;
	size_t	value_len;

	if (key == NULL)
		return (NULL);
	if (value == NULL)
	{
		value = ft_strdup("");
		if (value == NULL)
			exit_minishell(errno);
	}
	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	len = key_len + value_len + 2;
	keyvalue = (char *)minishell_calloc(len, sizeof(char));
	ft_strlcpy(keyvalue, key, key_len + 1);
	ft_strlcat(keyvalue, "=", len + 1);
	ft_strlcat(keyvalue, value, len + 1);
	return (keyvalue);
}
