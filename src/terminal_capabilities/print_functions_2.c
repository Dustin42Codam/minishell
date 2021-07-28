#include "terminal_capabilities.h"

#include <stdlib.h>

void	write_input_line(t_input_line *input_line)
{
	char			*str;
	t_input_line	*tmp;

	tmp = get_head_of_input_line(input_line);
	str = copy_input_line(input_line);
	minishell_putstr(str);
	free(str);
}

void	clear_input(t_prompt *prompt)
{
	int		row;
	int		col;
	int		rows_to_del;
	int		move_up_by_rows;
	char	*buf;

	buf = get_curent_cursor_pos();
	row = get_curent_row(buf);
	col = get_curent_col(buf, row);
	rows_to_del = get_row_per_input_line(prompt);
	move_up_by_rows = 0;
	while (rows_to_del >= 0)
	{
		rows_to_del--;
		del_curent_line();
		move_one_row_up(row - move_up_by_rows, col);
		move_up_by_rows++;
	}
	free(buf);
}

void	clear_input_2(t_prompt *prompt)
{
	int		row;
	int		rows_to_del;
	int		move_up_by_rows;
	char	*buf;

	buf = get_curent_cursor_pos();
	row = get_curent_row(buf);
	rows_to_del = get_row_per_input_line(prompt);
	move_up_by_rows = 0;
	while (rows_to_del > 0)
	{
		rows_to_del--;
		del_curent_line();
		move_one_row_up(row - move_up_by_rows, prompt->max_col);
		move_up_by_rows++;
	}
	free(buf);
}
