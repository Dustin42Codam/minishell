#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <errno.h>

t_prompt_keys	init_prompt_keys(void)
{
	return ((t_prompt_keys){"\x1b[A", "\x1b[B", "\x1b[C", "\x1b[D", "\x7f", "\n"});
}

t_prompt_color	init_prompt_color(void)
{
	return ((t_prompt_color){"\x1b[32;1;4m", "\x1b[34;1;4m",
		"\x1b[97;0;4m", "\x1b[0m"});
}

void	init_prompt(t_prompt **prompt)
{
	*prompt = ft_calloc(sizeof(t_prompt), 1);
	if (*prompt == NULL)
		exit_minishell(errno);
	(*prompt)->start_row = 0;
	(*prompt)->start_col = 0;
	(*prompt)->PS1 = get_prompt_message();
	(*prompt)->history = NULL;
	(*prompt)->input_line = NULL;
	(*prompt)->max_col = 0;
	(*prompt)->max_row = 0;
}

void	update_prompt(t_prompt **prompt)
{
	char		*buf;
	t_history	*hist;

	buf = get_curent_cursor_pos();
	(*prompt)->start_row = get_curent_row(buf);
	(*prompt)->start_col = get_curent_col(buf, (*prompt)->start_row);
	(*prompt)->max_col = get_max_amount_of_col();
	(*prompt)->max_row = get_max_amount_of_row();
	free(buf);
	hist = new_history_node(ft_strdup(""));
	(*prompt)->history = get_history_head((*prompt)->history);
	(*prompt)->tmp_history = ft_strdup("");
	if (is_string_NULL((*prompt)->tmp_history) == true)
		exit_minishell(errno);
	insert_node_history_start(&(*prompt)->history, hist);
	(*prompt)->input_line = NULL;
	free((*prompt)->PS1);
	(*prompt)->PS1 = get_prompt_message();
}
