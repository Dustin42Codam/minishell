#include "terminal_capabilities.h"

#include <stdlib.h>

void	ft_free_prompt(t_prompt *prompt)
{
	free(prompt->PS1);
	free(prompt);
}
