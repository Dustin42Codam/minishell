#include "minishell_termcap_signal.h"

#include <curses.h>
#include <term.h>

void	move_one_row_up(int row, int col)
{
	char	*mv_cursor;

	mv_cursor = "cm";
	tputs(tgoto(get_string_entry(mv_cursor), col, row), 1, &ft_putchar_ret_int);
}

void	move_one_row_down(int row, int col)
{
	char	*mv_cursor;

	mv_cursor = "cm";
	tputs(tgoto(get_string_entry(mv_cursor), col, row), 1, &ft_putchar_ret_int);
}

void	move_to_start_of_line(int row, int col)
{
	char	*mv_cursor;

	mv_cursor = "cm";
	tputs(tgoto(get_string_entry(mv_cursor), col, row), 1, &ft_putchar_ret_int);
}

void	move_to_start_row(int row, int col)
{
	char	*mv_cursor;

	mv_cursor = "cm";
	tputs(tgoto(get_string_entry(mv_cursor), col, row), 1, &ft_putchar_ret_int);
}

void	move_to_row_col(int row, int col)
{
	char	*mv_cursor;

	mv_cursor = "cm";
	tputs(tgoto(get_string_entry(mv_cursor), col, row), 1, &ft_putchar_ret_int);
}
