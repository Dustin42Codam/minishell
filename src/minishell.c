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

void	minishell_non_interactive(t_data *data, int argc, char *argv[])
{
	static const int	no_signal = 0;
	int					flags;

	data->interactive = FALSE;
	data->sig_NO = no_signal;
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
	exit(data->exit_status);
}

void	minishell_interactive(t_data *data)
{
	static const int	new_line_signal = 42;

	data->sig_NO = 42;
	data->interactive = TRUE;
	while (1)
	{
		if (data->sig_NO == SIGINT || data->sig_NO == new_line_signal)
			print_prompt(data->prompt);
		update_prompt(&data->prompt, data->sig_NO);
		data->sig_NO = ft_readline(&data->line, data->prompt);
		if (data->sig_NO == EOF)
			exit(data->exit_status);
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
}
