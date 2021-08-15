#include "minishell_termcap_signal.h"
#include "minishell.h"
#include <unistd.h>
//remove this hearders!
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	read_user_input(char *user_input)
{
/*	static int	fd = 0;

	if (fd == 0)
		fd = open("signals.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		exit_minishell(errno);*/
	const t_key_sizes	INVALID_LENGTH = INVALID_KEY;
	int					read_message_length;

	clear_user_input(user_input, 31);
	read_message_length = read(0, user_input, 31);
	if (read_message_length == INVALID_LENGTH)
		exit_minishell(errno);
/*	write(fd, "this is user input-> |", 20),
	write(fd, "|", 1);
	write(fd, user_input, ft_strlen(user_input));
	write(fd, "|", 1);
	write(fd, "|", 1);
	write(fd, ft_itoa(*user_input), ft_strlen(ft_itoa(*user_input)));
	write(fd, "|", 1);
	write(fd, " this is the len-> |", 20);
	write(fd, ft_itoa(ft_strlen(user_input)), ft_strlen(ft_itoa(ft_strlen(user_input))));
	write(fd, "|\n", 2);*/
	return (read_message_length);
}
