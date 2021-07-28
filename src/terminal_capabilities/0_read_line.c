#include "terminal_capabilities.h"
#include "minishell.h"
#include "libft.h"

#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

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

void	execute_user_input(char *user_input, t_prompt *prompt, int message_len)
{
	const t_key_sizes		LEN_ARROW_KEY = ARROW_KEY;
	const t_key_sizes		LEN_STANDART_KEY = STANDART_KEY;
	const t_prompt_keys		key = init_prompt_keys();

	if (message_len == LEN_STANDART_KEY)
	{
		if (ft_strncmp(key.DEL, user_input, STANDART_KEY) == false)
			del_char(prompt);
		else
			insert_char(user_input, prompt);
		update_tmp_history(&prompt);
	}
	if (message_len == LEN_ARROW_KEY)
		match_key_with_fuc(user_input, prompt);
}

int	read_user_input(char *user_input)
{
	const t_key_sizes	INVALID_LENGTH = INVALID_KEY;
	int					read_message_length;

	clear_user_input(user_input, 31);
	read_message_length = read(0, user_input, 31);
	if (read_message_length == INVALID_LENGTH)
		exit_minishell(errno);
	return (read_message_length);
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
	size = size_of_input_line_dll(input_line);
	line = ft_calloc(size + 2, sizeof(char));
	if (line == NULL)
		exit_minishell(errno);
	while (input_line)
	{
		line[index] = input_line->c;
		input_line = input_line->next;
		index++;
	}
	return (line);
}

void	ft_readline(char **line, t_prompt *prompt)
{
	char		user_input[32];
	int			message_length;

	clear_user_input(user_input, 31);
	while (true)
	{
		message_length = read_user_input(user_input);
		if (is_input_return(user_input) == true)
		{
			minishell_putstr("\n");
			break ;
		}
		execute_user_input(user_input, prompt, message_length);
	}
	*line = copy_input_line(prompt->input_line);
	prompt->history = get_history_head(prompt->history);
	update_node(&prompt, ft_strdup(*line));
}
