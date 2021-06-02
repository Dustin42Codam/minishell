#include "minishell.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
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

int	main(int argc, char *argv[], char **envp)
{
	t_data	*data;

	data = init_data(envp);
	while (1)
	{
		print_prompt();
		data->line_len = read_line(&data->line);
		if (errno)
			exit_shell(errno);
		
		/**
		 *  fake ctrl - d exit condition to be able to check for memleaks
		 * 	just use for debugging - delete later
		**/
		if (data->line_len == 0)
			break ;

		if (tokenizer(&data, data->line))
			printf("Syntax error!\n");
		else
		{
			#ifdef DEBUG_2
				t_token *token;
				token = data->token;
				while (token)
				{
					printf("[%s] [%d]\n", token->str, token->id);
					token = token->next;
				}
			#endif
			parse_astree(data);
			free_token_list(data->token);
			delete_ast(data->astree);
		}
		free(data->line);
		data->line = NULL;
	}
	(void)argc;
	(void)argv;
	free_data(data);
	return (0);
}
