#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <errno.h>
#include <term.h>

int	ft_putchar_ret_int(int c)
{
	const int	WRITE_FAILED = -1;

	if (write(1, &c, 1) == WRITE_FAILED)
		exit_minishell(errno);
	return (1);
}

char	*get_string_entry(char *key_id)
{
	char	*string_entry;
	char	*no_str_entry;

	no_str_entry = NULL;
	string_entry = tgetstr(key_id, NULL);
	if (string_entry == no_str_entry)
	{
		minishell_putstr("String entry is not found\n");
		exit_minishell(errno);
	}
	return (string_entry);
}

void	clear_user_input(char *buf, int size)
{
	const int	null_byte = 0;

	ft_memset(buf, null_byte, size);
}

void	copy_hist_to_tmp_hist(char *src, char **dest)
{
	free(*dest);
	*dest = ft_strdup(src);
	if (is_string_NULL(*dest) == true)
		exit_minishell(errno);
}

void	insert_char(char *user_input, t_prompt *prompt)
{
	int	rows_per_input_line;

	rows_per_input_line = 0;
	insert_node_input_line(&prompt->input_line,
		new_input_line_node(*user_input));
	if (prompt->start_row == prompt->max_row - 1)
	{
		rows_per_input_line = get_row_per_input_line(prompt);
		clear_input(prompt);
	}
	move_to_start_row(prompt->start_row - rows_per_input_line, 0);
	print_prompt(prompt);
	write_input_line(prompt->input_line);
	move_cursor_to_input_node(prompt);
}
