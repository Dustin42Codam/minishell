#include "minishell.h"
#include "expansion.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

static void	make_word_list(t_token	*token, char **words)
{
	size_t	i;

	i = 0;
	free(token->str);
	while (1)
	{
		token->str = words[i];
		token->type |= WORD;
		i++;
		if (words[i])
		{
			token->next = (t_token *)minishell_calloc(1, sizeof(t_token));
			token = token->next;
		}
		else
			break ;
	}
}

static int	check_split(char *str)
{
	if (ft_strchr(str, ' ') || ft_strchr(str, '\t') || ft_strchr(str, '\n'))
		return (TRUE);
	return (FALSE);
}

void	split_words(t_token *token)
{
	char	**words;
	t_token	*next_save;

	if (check_split(token->str) == FALSE)
		return ;
	next_save = token->next;
	words = word_splitter(token->str, " \t\n");
	if (words == NULL && errno)
		exit_minishell(errno);
	make_word_list(token, words);
	while (token->next)
		token = token->next;
	token->next = next_save;
}