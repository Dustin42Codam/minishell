#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->str);
		free(token);
		token = tmp;
	}
}

t_token	*init_token_list(size_t len)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(len + 1, sizeof(t_token));
	if (errno)
		exit_shell(errno);
	new_token->str = (char *)ft_calloc(len + 1, sizeof(char));
	if (errno)
		exit_shell(errno);
	return (new_token);
}

void	init_next_token(t_token **token, size_t len, size_t i)
{
	(*token)->next = (t_token *)ft_calloc(1, sizeof(t_token));
	if (errno)
		exit_shell(errno);
	(*token) = (*token)->next;
	(*token)->str = (char *)ft_calloc(len - i, sizeof(char));
	if (errno)
		exit_shell(errno);
}

static int	switch_ctype(t_data **data, t_token **token, size_t *i, size_t *j)
{
	char	c;
	int		ret;

	c = (*data)->line[(*i)];
	ret = 0;
	if (ft_strchr(" \n\t;<>|\"\'", c))
	{
		if ((*j) > 0)
			init_next_token(token, (*data)->line_len, *i);
		if (ft_strchr("<>|;", c))
			ret = token_meta(token, data, i, c);
		else if (ft_strchr("\"\'", c))
			ret = token_quote(token, data, i, c);
		(*j) = 0;
		return (ret);
	}
	else
	{
		(*token)->str[(*j)] = c;
		(*token)->id = WORD;
		(*j)++;
	}
	return (0);
}

void	handle_quotes(t_data *data)
{
	/**
	 * - parsing quotes -
	 * still has to be done
	 * currently just setting all quote token ids
	 * to zero so i can build and test the abstract syntax tree
	**/
	data->token_ptr = data->token;
	while (data->token_ptr)
	{
		if (data->token_ptr->id == SQUOTE || 
			data->token_ptr->id == DQUOTE)
			data->token_ptr->id = WORD;
		// if (data->token_ptr->next->)
		data->token_ptr = data->token_ptr->next;
	}
}

int	tokenizer(t_data **data, char *line)
{
	t_token		*tmp_token;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	(*data)->token = init_token_list((*data)->line_len);
	tmp_token = (*data)->token;
	while (line[i]/*  != '\n' */)
	{
		if (switch_ctype(data, &tmp_token, &i, &j))
			return (1);
		i++;
	}
	handle_quotes(*data);
	return (0);
}
