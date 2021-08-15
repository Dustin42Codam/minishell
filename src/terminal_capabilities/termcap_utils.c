#include "minishell_termcap_signal.h"
#include "minishell.h"
#include "libft.h"

void	clear_user_input(char *buf, int size)
{
	static const int	null_byte = 0;

	ft_memset(buf, null_byte, size);
}
