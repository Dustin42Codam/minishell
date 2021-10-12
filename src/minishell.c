/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:53:37 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:53:58 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

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

/*
**	THSE 2 HAVE MOORE THAN 25 LNIES
*/
void	minishell_non_interactive(t_data *data, int argc, char *argv[])
{
	int					flags;

	data->interactive = FALSE;
	if (argc > 1)
	{
		flags = read_flags(argc, argv);
		data->line = ft_strdup(argv[flags]);
	}
	else
		data->line = read_line();
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
		data->token_mask = 0;
	}
	free(data->line);
	data->line = NULL;
//Do we have to free data hear?
	exit(data->exit_status);
}

void	minishell_interactive(t_data *data)
{
	data->interactive = TRUE;
	while (1)
	{
		g_sig = 0;
		data->line = readline("minishell$ ");
		if (g_sig == 1)
			data->exit_status = 1;
		if (data->line == NULL)
			return ;
		errno = 0;
		if (ft_strlen(data->line) != 0)
			add_history(data->line);
		data->line_len = ft_strlen(data->line);
		if (lexer(&data, data->line) == EXIT_FAILURE)
			printf("Syntax error!\n");
		else
		{
			parser(data);
			execute(data);
			delete_ast(data->astree);
			free_token_list(data->token);
			data->token_mask = 0;
		}
		free(data->line);
		data->line = NULL;
	}
}
