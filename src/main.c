#include "executor.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

#include <stdlib.h>
#include <errno.h>

int	g_sig;

static void	init_terminal(t_data *data)
{
	char		*term_name;

	term_name = getenv("TERM");
	if (term_name == NULL)
		exit_minishell(errno);
	tcgetattr(0, &data->old_term);
	data->new_term = data->old_term;
	data->new_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &data->new_term);
	if (tgetent(0, term_name) == -1)
		exit_minishell_custom(
			"Name of type of data->new_terminal is unknown fix $env\n");
}

int	main(int argc, char *argv[], char **envp)
{
	t_data			*data;

	g_sig = 0;
	data = init_data(envp);
	init_terminal(data);
	if (argc == 1)
		minishell_interactive(data);
	else
		minishell_non_interactive(data, argc, argv);
	free_data(data);
	return (0);
}
