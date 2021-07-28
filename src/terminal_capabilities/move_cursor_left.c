#include "terminal_capabilities.h"
#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>

bool	is_cursor_at_start_of_line(int col)
{
	if (col == 0)
		return (true);
	else
		return (false);
}

bool	is_cursor_on_prompt(t_prompt *prompt, int row, int col)
{
	t_input_line	*li;
	int				size;

	li = get_head_of_input_line(prompt->input_line);
	size = size_of_input_line_dll(li) + (int)ft_strlen(prompt->PS1);
	if ((row == (prompt->max_row - 1)) && size > prompt->max_col)
		return (false);
	else if (row == prompt->start_row && prompt->start_col >= col)
		return (true);
	else
		return (false);
}

bool	can_move_cursor_left(t_prompt *prompt, int row, int col)
{
	if (is_cursor_on_prompt(prompt, row, col) == true
		|| is_previus_input_line_node_null(prompt->input_line) == true)
		return (false);
	else
		return (true);
}

static bool	move_left(t_prompt *prompt, int col, int last_column, int row)
{
	if (is_cursor_at_start_of_line(col) == true)
	{
		move_one_row_up(row - 1, col);
		move_to_end_of_line(row - 1, last_column - 1);
	}
	else
		move_left_one_space();
	if (is_input_line_node_null(prompt) == true)
		return (true);
	if (is_previus_input_line_node_null(prompt->input_line) == false)
		prompt->input_line = prompt->input_line->previus;
	return (true);
}

bool	react_to_left_arrow_key_press(t_prompt *prompt)
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
		return (move_left(prompt, col, last_column, row));
	else
	{
		ring_bell();
		return (false);
	}
}
