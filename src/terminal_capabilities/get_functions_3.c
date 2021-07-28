#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <errno.h>
#include <curses.h>
#include <term.h>

int	get_max_amount_of_col(void)
{
	int			max_col;
	char		*max_col_id;
	const int	max_col_id_not_availabe = -1;

	max_col_id = "co";
	max_col = tgetnum(max_col_id);
	if (max_col == max_col_id_not_availabe)
		exit_minishell(errno);
	return (max_col);
}

int	get_max_amount_of_row(void)
{
	int			max_row;
	char		*max_row_id;
	const int	max_row_id_not_availabe = -1;

	max_row_id = "li";
	max_row = tgetnum(max_row_id);
	if (max_row == max_row_id_not_availabe)
		exit_minishell(errno);
	return (max_row);
}

char	*get_curent_cursor_pos(void)
{
	char	*buf;

	buf = ft_calloc(32, sizeof(char));
	if (buf == NULL)
		exit_minishell(errno);
	ask_cursor_position(1);
	recive_cursor_position(buf, 0);
	return (buf);
}
