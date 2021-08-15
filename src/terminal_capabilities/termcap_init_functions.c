#include "minishell_termcap_signal.h"
#include "minishell.h"
#include "libft.h"

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
	*prompt = minishell_calloc(sizeof(t_prompt), 1);
	(*prompt)->start_row = 0;
	(*prompt)->start_col = 0;
	(*prompt)->PS1 = get_prompt_message();
	(*prompt)->history = NULL;
	(*prompt)->input_line = NULL;
	(*prompt)->max_col = 0;
	(*prompt)->max_row = 0;
	(*prompt)->signals = init_signals();
}

void	insert_new_node_hist(t_prompt **prompt)
{
	t_history	*hist;

	hist = new_history_node(ft_strdup(""));
	(*prompt)->history = get_history_head((*prompt)->history);
	(*prompt)->tmp_history = ft_strdup("");
	if (is_string_NULL((*prompt)->tmp_history) == true)
		exit_minishell(errno);
	insert_node_history_start(&(*prompt)->history, hist);
}

void	update_prompt(t_prompt **prompt, int sig)
{
	char		*buf;
	const static int	new_line_sig = 42;

	buf = get_curent_cursor_pos();
	(*prompt)->start_row = get_curent_row(buf);
	(*prompt)->start_col = get_curent_col(buf, (*prompt)->start_row);
	free(buf);
	(*prompt)->max_col = get_max_amount_of_col();
	(*prompt)->max_row = get_max_amount_of_row();
	if (sig == new_line_sig)
	{
		if ((*prompt)->history == NULL)
			insert_new_node_hist(prompt);
		else
		{
			if (ft_strlen((*prompt)->history->str) != 0)
				insert_new_node_hist(prompt);
		}
	}
	(*prompt)->input_line = NULL;
	free((*prompt)->PS1);
	(*prompt)->PS1 = get_prompt_message();
}
