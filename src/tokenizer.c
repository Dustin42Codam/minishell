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
		token->str = NULL;
		free(token);
		token = NULL;
		token = tmp;
	}
}

static t_token	*init_token_list(size_t len)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(len, sizeof(t_token));
	if (errno)
		exit_shell(errno);
	new_token->str = (char *)ft_calloc(len, sizeof(char));
	if (errno)
		exit_shell(errno);
	new_token->id = WORD;
	new_token->next = NULL;
	return (new_token);
}

int	init_next_token(t_token **token, size_t len, size_t i)
{
	(*token)->next = (t_token *)ft_calloc(1, sizeof(t_token));
	if (errno)
		exit_shell(errno);
	(*token) = (*token)->next;
	(*token)->str = (char *)ft_calloc(len - i, sizeof(char));
	if (errno)
		exit_shell(errno);
	(*token)->next = NULL;
	return (0);
}

static int	switch_ctype(t_data **data, t_token **token, size_t *i, size_t *j)
{
	char	c;
	int		ret;

	c = (*data)->line[(*i)];
	if (ft_strchr(" \t\n;<>|\"\'", c))
	{
		if ((*j) > 0)
			ret = init_next_token(token, (*data)->line_len, *i);
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

int	tokenizer(t_data **data, char *line)
{
	t_token		*tmp_token;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	(*data)->token = init_token_list((*data)->line_len);
	tmp_token = (*data)->token;
	while (line[i])
	{
		if (switch_ctype(data, &tmp_token, &i, &j))
			return (1);
		i++;
	}
	return (0);
}
