#include "libft.h"
#include "minishell.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void	handel_sig(int signal)
{
	int	retVal;

	retVal = fork();
	if (signal == SIGINT)
		kill(retVal, SIGKILL);
}


pid_t	call(char *line)
{
	char	*envp[] = {NULL};
	char	*args[] = {"", NULL};
	pid_t	pid;

	args[0] = ft_strjoin("/bin/", line);
	if (errno)
		exit_shell(errno);
	pid = fork();
	if (pid == 0)
	{
		printf("one :%s 2: %s", args[0], args[1]);
		execve(args[0], args, envp);
		perror("Could not execve");
		exit(1);
	}
	return pid;
}
