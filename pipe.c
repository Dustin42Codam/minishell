/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 15:04:06 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/14 18:49:22 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	int	pid;
	int	stat;
	int	save_stdin = dup(0);
	int	save_stdout = dup(1);
	int	pid_head;
	int	fd[2];
	char *args[3] = {"/bin/cat", "/dev/random", NULL};

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve("/bin/cat", args, envp);
	}
	else
	{
		pid_head = fork();
		if (pid_head == 0)
		{
			char *args2[3] = {"/bin/head", "-3", NULL};
			dup2(fd[0], 0);
			close(fd[1]);
			execve("/bin/head", args2, envp);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, &stat, 0);
		printf("%d\n", stat);
		if (WIFSIGNALED(stat))
			printf("signaled\n");
		if (WIFEXITED(stat))
			printf("exited\n");
	}
	return (0);
}
