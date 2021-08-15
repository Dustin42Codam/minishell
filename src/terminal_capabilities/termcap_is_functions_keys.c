#include "minishell_termcap_signal.h"

#include <stdbool.h>

bool	is_input_key_left_arrow(char *c)
{
	const t_prompt_keys	key = init_prompt_keys();
	const int			size = 3;

	return (is_str_key(key.LEFT, c, size));
}

bool	is_input_key_right_arrow(char *c)
{
	const t_prompt_keys	key = init_prompt_keys();
	const int			size = 3;

	return (is_str_key(key.RIGHT, c, size));
}

bool	is_input_key_up_arrow(char *c)
{
	const t_prompt_keys	key = init_prompt_keys();
	const int			size = 3;

	return (is_str_key(key.UP, c, size));
}

bool	is_input_key_down_arrow(char *c)
{
	const t_prompt_keys	key = init_prompt_keys();
	const int			size = 3;

	return (is_str_key(key.DOWN, c, size));
}

bool	is_input_return(char *user_input)
{
	const t_prompt_keys	key = init_prompt_keys();
	const int			size = 1;

	return (is_str_key(key.RETURN, user_input, size));
}
