#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
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

void	init_new_token(t_token **token, size_t len, size_t *j)
{
	if (len <= 1)
		len = 2;
	if ((*token)->type != EMPTY)
	{
		(*token)->next = (t_token *)ft_calloc(1, sizeof(t_token));
		if (errno)
			exit_shell(errno);
		(*token) = (*token)->next;
		(*token)->str = (char *)ft_calloc(len, sizeof(char));
		if (errno)
			exit_shell(errno);
		(*j) = 0;
	}
}

static void	analyze_char(t_data **data, t_token **token, size_t *i, size_t *j)
{
	char	c;

	c = (*data)->line[(*i)];
	if (is_break(c) || is_quote(c))
		init_new_token(token, (*data)->line_len - (*i), j);
	if (is_meta(c))
		make_token_meta(token, data, i, j);
	else if (is_quote(c))
		make_token_quote(token, data, i, j);
	else if (is_blank(c) == NULL && (*data)->error == FALSE)
	{
		if (c == '\\')
		{
			(*i)++;
			c = (*data)->line[(*i)];
		}
		else if (c == '$')
			(*token)->type |= EXPAND;
		(*token)->str[(*j)] = c;
		if (is_end(c) == NULL)
			(*token)->type |= WORD;
		(*j)++;
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
	while (line[i] && (*data)->error == FALSE)
	{
		analyze_char(data, &tmp_token, &i, &j);
		i++;
	}
	if ((*data)->error == TRUE)
	{
		(*data)->error = FALSE;
		return (EXIT_FAILURE);
	}
	print_token_types((*data)->token);
	return (EXIT_SUCCESS);
}
