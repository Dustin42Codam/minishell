#include "minishell.h"
#include "get_next_line.h"
#include "libft.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

static void	print_prompt(void)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cwd)
	{
		ft_putstr(BGRN);
		ft_putstr("@minishell");
		ft_putstr(WHT);
		ft_putchar(':');
		ft_putstr(BBLU);
		ft_putstr(cwd);
		ft_putstr(WHT);
		ft_putstr("$ ");
		ft_putstr(END);
		free(cwd);
	}
	if (errno)
		exit_shell(errno);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	while (1)
	{
		print_prompt();
		get_next_line(0, &data->line);
		if (errno)
			exit_shell(errno);
		data->line_len = ft_strlen(data->line);
		if (tokenizer(&data, data->line))
			printf("Syntax error!\n");
		#ifdef DEBUG_2
			t_token *token;
			token = data->token;
			while (token)
			{
				printf("[%s] [%d]\n", token->str, token->id);
				token = token->next;
			}
		#endif
		free_token_list(data->token);
		free(data->line);
		data->line = NULL;
	}
	free(data);
	return (0);
}
