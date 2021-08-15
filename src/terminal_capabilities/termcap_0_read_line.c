#include "minishell_termcap_signal.h"
#include "minishell.h"
#include "libft.h"

#include <errno.h>

void	match_key_with_fuc(char *user_input, t_prompt *prompt)
{
	if (is_input_key_left_arrow(user_input) == true)
		react_to_left_arrow_key_press(prompt);
	else if (is_input_key_right_arrow(user_input) == true)
		react_to_right_arrow_key_press(prompt);
	else if (is_input_key_up_arrow(user_input) == true)
		history_travers(prompt);
	else if (is_input_key_down_arrow(user_input) == true)
		history_revers(prompt);
	else
		return ;
}

int	execute_user_input(char *user_input, t_prompt *prompt, int message_len)
{
	static const int		LEN_ARROW_KEY = 3;
	static const int		NOT_REGISTERED_KEY = 42;
	static const int		DEFAULT_EXIT = 42;

	if (is_regular_key_or_sig(message_len))
	{
		if (is_del_char(user_input))
			del_char(prompt);
		else if (is_signal(*user_input, prompt->signals) == true)
			return (call_function_by_sig(user_input, prompt));
		else if (is_regular_char(*user_input))
		{
			insert_char(user_input, prompt);
			update_tmp_history(&prompt);
		}
		else
			return (NOT_REGISTERED_KEY);
	}
	if (message_len == LEN_ARROW_KEY)
		match_key_with_fuc(user_input, prompt);
	return (DEFAULT_EXIT);
}

/*
**	ft_read_line mimic's systeam readline
**	lets finih this and then  think about di
*/

char	*copy_input_line(t_input_line *input_line)
{
	size_t	size;
	char	*line;
	size_t	index;

	index = 0;
	input_line = get_head_of_input_line(input_line);
	size = get_size_of_input_line_dll(input_line);
	line = minishell_calloc(sizeof(char), size + 2);
	while (input_line)
	{
		line[index] = input_line->c;
		input_line = input_line->next;
		index++;
	}
	return (line);
}

#include <stdio.h>
#include <stdlib.h>

int	ft_readline(char **line, t_prompt *prompt)
{
	char		user_input[32];
	int			message_length;
	int			sig_NO;
	const static int	new_line_sig = 42;

	clear_user_input(user_input, 31);
	sig_NO = 42;
	while (sig_NO == 42)
	{
		message_length = read_user_input(user_input);
		if (is_input_return(user_input) == true)
		{
			minishell_putstr("\n");
			*line = copy_input_line(prompt->input_line);
			prompt->history = get_history_head(prompt->history);
			update_node(&prompt, ft_strdup(*line));
			return (new_line_sig);
		}
		sig_NO = execute_user_input(user_input, prompt, message_length);
	}
	if (sig_NO == SIGINT)
	{
		minishell_putstr("\n");
		prompt->history = get_history_head(prompt->history);
		free(prompt->tmp_history);
		prompt->tmp_history = ft_strdup("");
		if (is_string_NULL(prompt->tmp_history))
			exit_minishell(errno);
	}
	*line = ft_strdup("");
	if (is_string_NULL(*line))
		exit_minishell(errno);
	return (sig_NO);
}
