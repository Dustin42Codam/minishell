#include "minishell_termcap_signal.h"

#include <stdlib.h>

static void	continue_2(t_prompt *prompt)
{
	pop_a_node_input_line(&prompt->input_line);
	clear_input(prompt);
	move_to_start_row(prompt->start_row, 0);
	print_prompt(prompt);
	write_input_line(prompt->input_line);
	move_cursor_to_input_node(prompt);
}

void	del_char(t_prompt *prompt)
{
	int		row;
	int		col;
	char	*buf;
	int		last_column;

	last_column = prompt->max_col;
	buf = get_curent_cursor_pos();
	row = get_curent_row(buf);
	col = get_curent_col(buf, row);
	free(buf);
	if (can_move_cursor_left(prompt, row, col) == true)
	{
		if (is_cursor_at_start_of_line(col) == true)
		{
			move_one_row_up(row - 1, col);
			move_to_end_of_line(row - 1, last_column);
		}
		else
			move_left_one_space();
		if (is_input_line_node_null(prompt) == true)
			return ;
		continue_2(prompt);
	}
	else
		ring_bell();
}
