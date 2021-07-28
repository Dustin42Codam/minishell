#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>

void	minishell_putstr(char *str)
{
	const int	write_failed = -1;
	int			size;

	size = ft_strlen(str);
	if (write(1, str, size) == write_failed)
		exit_minishell(errno);
}

char	*apply_color(char *message, char *color)
{
	const t_prompt_color	prompt_color = init_prompt_color();
	char					*tmp;

	message = ft_strjoin(color, "@minishell");
	if (is_string_NULL(message) == true)
		exit_minishell(errno);
	tmp = ft_strdup(message);
	free(message);
	message = ft_strjoin(tmp, prompt_color.ESC_COLOR);
	if (is_string_NULL(message) == true)
		exit_minishell(errno);
	free(tmp);
	return (message);
}

void	print_input_line(char *line)
{
	minishell_putstr(line);
}

void	print_prompt(t_prompt *prompt)
{
	minishell_putstr(prompt->PS1);
}

/*
*************************************************
**	insert mode:				|
**	instead of overwrting a char		|
**	all chars will be pushed to the		|
**	left alowing to eddit insert chars in	|
**	in the middle of the line		|
*************************************************
*/

int	write_to_stdout(char *str)
{
	const int	write_failed = -1;
	const int	STDOUT = 1;

	open_insert_mode();
	if (write(STDOUT, str, 1) == write_failed)
	{
		escape_insert_mode();
		return (-1);
	}
	escape_insert_mode();
	return (0);
}
