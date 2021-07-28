#include "terminal_capabilities.h"

#include <curses.h>
#include <term.h>

void	move_left_one_space(void)
{
	char	*move_left_id;

	move_left_id = "le";
	tputs(get_string_entry(move_left_id), 1, &ft_putchar_ret_int);
}

void	move_right_one_space(void)
{
	char	*move_cursoe_right_id;

	move_cursoe_right_id = "nd";
	tputs(get_string_entry(move_cursoe_right_id), 1, &ft_putchar_ret_int);
}

void	ring_bell(void)
{
	char	*bell_id;

	bell_id = "bl";
	tputs(get_string_entry(bell_id), 1, &ft_putchar_ret_int);
}

void	delet_char_at_cursor_pos(void)
{
	char	*delete_char_id;

	delete_char_id = "dc";
	tputs(get_string_entry(delete_char_id), 1, &ft_putchar_ret_int);
}
