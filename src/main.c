#include "terminal_capabilities.h"
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

static void	init_terminal(struct termios *term)
{
	char		*term_name;

	term_name = getenv("TERM");
	if (term_name == NULL)
		exit_minishell(errno);
	tcgetattr(0, term);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(VERASE);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, term);
	if (tgetent(0, term_name) == -1)
		exit_minishell_custom("Name of type of terminal is unknown fix $env\n");
}

int	main(int argc, char *argv[], char **envp)
{
	struct termios	term;
	t_prompt		*prompt;
	t_data			*data;

	init_terminal(&term);
	init_prompt(&prompt);
	data = init_data(envp);
	data->prompt = prompt;
	if (argc == 1)
		minishell_interactive(data);
	else
		minishell_non_interactive(data, argc, argv);
	free_data(data);
	return (0);
}
