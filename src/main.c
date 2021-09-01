#include "executor.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

int	g_sig;

int	main(int argc, char *argv[], char **envp)
{
	t_data			*data;

	g_sig = 0;
	data = init_data(envp);
	if (argc == 1)
		minishell_interactive(data);
	else
		minishell_non_interactive(data, argc, argv);
	free_data(data);
	return (0);
}
