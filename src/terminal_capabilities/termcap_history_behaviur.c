#include "minishell_termcap_signal.h"
#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

#include <unistd.h>

int	get_row_per_input_line(t_prompt *prompt)
{
	int				size;
	int				rows;
	t_input_line	*li;

	li = get_head_of_input_line(prompt->input_line);
	size = get_size_of_input_line_dll(li);
	rows = (size + (int)ft_strlen(prompt->PS1)) / prompt->max_col;
	return (rows);
}

void	clear_history(t_prompt *prompt)
{
	int		row;
	int		col;
	char	*buf;
	int		rows_to_del;
	int		move_up_by_rows;

	buf = get_curent_cursor_pos();
	row = get_curent_row(buf);
	col = get_curent_col(buf, row);
	rows_to_del = get_row_per_input_line(prompt);
	move_up_by_rows = 1;
	while (rows_to_del >= 0)
	{
		rows_to_del--;
		del_curent_line();
		move_one_row_up(row - move_up_by_rows, col);
		move_up_by_rows++;
	}
	free(buf);
}

void	history_revers(t_prompt *prompt)
{
	if (is_history_null(prompt) == true)
		ring_bell();
	else
	{
		if (is_previus_history_node_null(prompt))
			ring_bell();
		else
		{
			update_history_node(&prompt->history, prompt->tmp_history);
			prompt->history = prompt->history->previus;
			clear_history(prompt);
			move_to_start_of_line(prompt->start_row, 0);
			print_prompt(prompt);
			minishell_putstr(prompt->history->str);
			if (is_previus_input_line_node_null(prompt->input_line) == false)
				prompt->input_line = get_head_of_input_line(prompt->input_line);
			clear_input_line(&prompt->input_line);
			copy_hist_to_input_line(prompt->history->str, &prompt->input_line);
			copy_hist_to_tmp_hist(prompt->history->str, &prompt->tmp_history);
		}
	}
}

void	history_travers(t_prompt *prompt)
{
	if (is_history_null(prompt) == true)
		ring_bell();
	else
	{
		if (is_next_history_node_null(prompt))
			ring_bell();
		else
		{
			update_history_node(&prompt->history, prompt->tmp_history);
			prompt->history = prompt->history->next;
			del_curent_line();
			move_to_start_of_line(prompt->start_row, 0);
			print_prompt(prompt);
			minishell_putstr(prompt->history->str);
			if (is_previus_input_line_node_null(prompt->input_line) == false)
				prompt->input_line = get_head_of_input_line(prompt->input_line);
			clear_input_line(&prompt->input_line);
			copy_hist_to_input_line(prompt->history->str, &prompt->input_line);
			copy_hist_to_tmp_hist(prompt->history->str, &prompt->tmp_history);
		}
	}
}
