#include "minishell_termcap_signal.h"
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

static void	init_terminal(t_data *data)
{
	char		*term_name;

	term_name = getenv("TERM");
	if (term_name == NULL)
		exit_minishell(errno);
	tcgetattr(0, &data->old_term);
	data->new_term = data->old_term;
	data->new_term.c_lflag &= ~(ECHO);
	data->new_term.c_lflag &= ~(ICANON);
	data->new_term.c_lflag &= ~(VERASE);
	data->new_term.c_lflag &= ~(ISIG);
	data->new_term.c_cc[VMIN] = 1;
	data->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &data->new_term);
	if (tgetent(0, term_name) == -1)
		exit_minishell_custom(
			"Name of type of data->new_terminal is unknown fix $env\n");
}

int	main(int argc, char *argv[], char **envp)
{
	t_prompt		*prompt;
	t_data			*data;

	data = init_data(envp);
	init_terminal(data);
	init_prompt(&prompt);
	data->prompt = prompt;
	if (argc == 1)
		minishell_interactive(data);
	else
		minishell_non_interactive(data, argc, argv);
	free_data(data);
	return (0);
}
