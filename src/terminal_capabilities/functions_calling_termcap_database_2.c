#include "terminal_capabilities.h"

#include <curses.h>
#include <term.h>

void	escape_insert_mode(void)
{
	char	*escape_insert_mode_id;

	escape_insert_mode_id = "ei";
	tputs(get_string_entry(escape_insert_mode_id), 0, &ft_putchar_ret_int);
}

void	open_insert_mode(void)
{
	char	*open_insert_mode_id;

	open_insert_mode_id = "im";
	tputs(get_string_entry(open_insert_mode_id), 0, &ft_putchar_ret_int);
}

void	move_move_row_down(void)
{
	char	*move_to_next_row_id;

	move_to_next_row_id = "Zz";
	tputs(get_string_entry(move_to_next_row_id), 0, &ft_putchar_ret_int);
}

void	del_curent_line(void)
{
	char	*del_line_id;

	del_line_id = "dl";
	tputs(get_string_entry(del_line_id), 1, &ft_putchar_ret_int);
}

void	move_to_end_of_line(int row, int col)
{
	char	*mv_cursor;

	mv_cursor = "cm";
	tputs(tgoto(get_string_entry(mv_cursor), col, row), 1, &ft_putchar_ret_int);
}
