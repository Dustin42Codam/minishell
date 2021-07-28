#include "terminal_capabilities.h"

bool	can_move_right(t_prompt *prompt, int row, int col)
{
	int				curent_col;
	int				row_diff;
	const int		size_of_pad = 1;
	t_input_line	*input_line;

	row_diff = prompt->start_row;
	input_line = get_head_of_input_line(prompt->input_line);
	curent_col = prompt->start_col + size_of_input_line_dll(input_line)
		- size_of_pad;
	if (curent_col > prompt->max_col)
	{
		curent_col -= prompt->max_col;
		row_diff++;
	}
	if ((row == row_diff && col >= curent_col)
		|| is_next_input_line_node_null(prompt) == true)
		return (false);
	else
		return (true);
}
