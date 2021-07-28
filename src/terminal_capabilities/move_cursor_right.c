#include "terminal_capabilities.h"

#include <stdlib.h>

void	react_to_right_arrow_key_press(t_prompt *prompt)
{
	char		*buf;
	int			col;
	int			row;

	buf = get_curent_cursor_pos();
	row = get_curent_row(buf);
	col = get_curent_col(buf, row);
	free(buf);
	if (can_move_right(prompt, row, col) == true)
	{
		if (is_cursor_at_lats_column(*prompt, col + 1) == true)
		{
			move_one_row_down(row + 1, col);
			move_to_start_of_line(row + 1, 0);
		}
		else
			move_right_one_space();
		if (is_input_line_node_null(prompt) == true)
			return ;
		if (is_next_input_line_node_null(prompt) == false)
			prompt->input_line = prompt->input_line->next;
	}
	else
		ring_bell();
}
