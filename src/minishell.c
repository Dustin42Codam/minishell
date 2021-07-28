#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static int	check_option_flag(char *arg)
{
	size_t	i;

	if (!arg[0] || arg[0] != '-' || !arg[1])
		return (0);
	if (arg[1] != 'c')
		exit_minishell(2);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'c')
			exit_minishell(2);
		i++;
	}
	return (1);
}

static int	read_flags(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc && check_option_flag(argv[i]))
		i++;
	if (i == argc)
	{
		printf("minishell: -c: option requires an argument\n");
		exit_minishell(2);
	}
	return (i);
}

void	non_interactive_shell(t_data *data, int argc, char *argv[])
{
	int	flags;

	data->interactive = FALSE;
	flags = read_flags(argc, argv);
	data->line = ft_strdup(argv[flags]);
	if (data->line == NULL)
		exit_minishell(errno);
	data->line_len = ft_strlen(data->line);
	if (lexer(&data, data->line) == EXIT_FAILURE)
		printf("Syntax error!\n");
	else
	{
		parser(data);
		execute(data);
		delete_ast(data->astree);
		free_token_list(data->token);
	}
	free(data->line);
	data->line = NULL;
}

void	interactive_shell(t_data *data)
{
	data->interactive = TRUE;
	while (1)
	{
		print_prompt(data->prompt);
		update_prompt(&data->prompt);
		ft_readline(&data->line, data->prompt);
		data->line_len = ft_strlen(data->line);
		if (data->line == NULL)
			exit_minishell(errno);
		if (lexer(&data, data->line) == EXIT_FAILURE)
			printf("Syntax error!\n");
		else
		{
			parser(data);
			execute(data);
			delete_ast(data->astree);
			free_token_list(data->token);
		}
		free(data->line);
		data->line = NULL;
	}
}
