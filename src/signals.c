#include "libft.h"
#include "minishell.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


void	handel_sig(int signal)
{
	int	retVal;

	retVal = fork();
	if (signal == SIGINT)
		kill(retVal, SIGKILL);
}

int	call(char *line)
{
	char		*env;
//	char	*args[] = {"", NULL};
	char		**parts;
	pid_t		pid;
	int		index;

//	args[0] = ft_strjoin("/bin/", line);
	index = 0;
	env = getenv("PATH");
	printf("this is env %s\n", env);
	parts = ft_split(line, ' ');
	while (parts[index])
	{
		printf("this is parts %s\n", parts[index]);
		index++;
	}
	if (errno)
		exit_minishell(errno);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
	/*
		printf("one :%s 2: %s", args[0], args[1]);
		execve(args[0], args, envp);
		perror("Could not execve");
		exit(1);
	*/
	}
	return pid;
}
