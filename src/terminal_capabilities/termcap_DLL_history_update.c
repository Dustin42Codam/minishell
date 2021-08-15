#include "minishell_termcap_signal.h"
#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <errno.h>

void	update_node(t_prompt **prompt, char *updated_line)
{
	if (updated_line == NULL)
		exit_minishell(errno);
	free((*prompt)->history->str);
	(*prompt)->history->str = updated_line;
}

void	update_line(t_prompt **prompt)
{
	char	*str;

	str = copy_input_line((*prompt)->input_line);
	update_node(prompt, str);
}

void	update_history_node(t_history **dest, char *src)
{
	free((*dest)->str);
	(*dest)->str = ft_strdup(src);
	if (is_string_NULL((*dest)->str) == true)
		exit_minishell(errno);
}

void	update_tmp_history(t_prompt **prompt)
{
	char	*str;

	str = copy_input_line((*prompt)->input_line);
	if (is_string_NULL(str) == true)
		exit_minishell(errno);
	free((*prompt)->tmp_history);
	(*prompt)->tmp_history = str;
}
