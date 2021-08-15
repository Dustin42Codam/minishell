#include "minishell_termcap_signal.h"

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
