#include "minishell_termcap_signal.h"

#include <stdlib.h>

void	ft_free_prompt(t_prompt *prompt)
{
	free(prompt->PS1);
	free(prompt);
}
