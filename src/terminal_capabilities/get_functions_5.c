#include "terminal_capabilities.h"
#include "minishell.h"

#include <unistd.h>
#include <errno.h>
#include <term.h>

void	ask_cursor_position(int ttyfd)
{
	const char	*code = "\x1b[6n";
	const int	code_length = 4;

	if (write(ttyfd, code, code_length) != code_length)
		exit_minishell(errno);
}

/*
**	sometimes curent_row and current colum m8 fail
**	for unknow reason write(1, "\x1B[6n", 4)
**	read(STDIN_FILENO, buf, 4) read or write will fail
**	and columns are rows will be equal to 0
**	there for we run this code in a loop till we get
**	the neccessay input
*/

int	failed_to_write_exit_code(char *buf)
{
	if (buf[0] != '\x1b' || buf[1] != '[')
		return (1);
	return (0);
}

void	recive_cursor_position(char *buf, int ttyfd)
{
	const int	READ_FAILED = -1;
	int			read_ret;
	int			index;

	index = 0;
	read_ret = 1;
	while (read_ret)
	{
		read_ret = read(ttyfd, buf + index, 1);
		if (read_ret == READ_FAILED)
			exit_minishell(errno);
		if (buf[index] == 'R')
			break ;
		index++;
	}
}

t_history	*get_history_head(t_history *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->previus != NULL)
		lst = lst->previus;
	return (lst);
}
