/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:56:52 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:57:46 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include <errno.h>
#include <stdlib.h>

int	get_next_token(t_data *data, char **token_str, int token_type)
{
	if (data->token_ptr->type == EMPTY)
		return (EXIT_FAILURE);
	else if (data->token_ptr->type & token_type)
	{
		if (token_str)
		{
			*token_str = ft_strdup(data->token_ptr->str);
			if (*token_str == NULL)
				exit_minishell(errno);
		}
		data->token_ptr = data->token_ptr->next;
		return (EXIT_SUCCESS);
	}
	data->token_ptr = data->token_ptr->next;
	return (EXIT_FAILURE);
}

void	parser(t_data *data)
{
	data->token_ptr = data->token;
	data->astree = parse_pipeline(data);
}
