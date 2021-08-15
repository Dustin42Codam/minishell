#include "minishell_termcap_signal.h"
#include "libft.h"

bool	is_regular_key_or_sig(int message_len)
{
	static const int	LEN_SIG = 1;
	static const int	LEN_REG_KEY = 1;

	if (message_len == LEN_SIG ||
		message_len == LEN_REG_KEY)
		return (true);
	else
		return (false);
}

bool	is_signal(char user_input, t_signals *signals)
{
	static const int	SIGNAL_IS_REGISTERED = true;
	static const int	SIGNAL_IS_NOT_REGISTERED = false;
	t_signals		*tmp;

	tmp = signals;
	while (tmp)
	{
		if (tmp->signal_char == (int)user_input)
			return (SIGNAL_IS_REGISTERED);
		tmp = tmp->next;
	}
	return (SIGNAL_IS_NOT_REGISTERED);
}

bool	is_del_char(char *user_input)
{
	const t_prompt_keys	key = init_prompt_keys();
	static const int	REGULAR_KEY = 1;

	if (ft_strncmp(key.DEL, user_input, REGULAR_KEY) == false)
		return (true);
	else
		return (false);
}

bool	is_regular_char(char user_input)
{
	if (ft_isascii(user_input) || user_input == '\t')
		return (true);
	else
		return (false);
}
