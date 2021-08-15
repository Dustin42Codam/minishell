#include "minishell_termcap_signal.h"
#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <errno.h>

void	copy_hist_to_tmp_hist(char *src, char **dest)
{
	free(*dest);
	*dest = ft_strdup(src);
	if (is_string_NULL(*dest) == true)
		exit_minishell(errno);
}
