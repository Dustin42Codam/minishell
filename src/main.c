/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:57:07 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/10/28 15:41:43 by alkrusts      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"
#include "lexer.h"

#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int	g_sig;

int	main(int argc, char *argv[], char **envp)
{
	t_data			*data;
	int				exit_status;

	g_sig = 0;
	if (signal(SIGINT, sig_int_parent) == SIG_ERR)
		exit_minishell_custom("Error SIGINT ");
	if (signal(SIGQUIT, sig_quit_parent) == SIG_ERR)
		exit_minishell_custom("Error SIGQUIT ");
	data = init_data(envp);
	if (argc == 1)
	{
		data->interactive = TRUE;
		minishell_interactive(data);
	}
	else
	{
		errno = 0;
		minishell_non_interactive(data, argc, argv);
	}
	exit_status = data->exit_status;
	free_data(data);
	return (exit_status);
}
