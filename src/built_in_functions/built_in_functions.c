#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

/*
**	if index == 1 then the tokens is only cd;
**	
*/

int	mini_cd(char *arg)
{
	if (arg == NULL)
		arg = getenv("HOME");
	if (chdir(arg) < 0)
		return (0);
	else
		return (1);
}

/*
**The pwd utility exits 0 on success, and >0 if an error occurs
*/

int	mini_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	else
		return (!printf("%s\n", cwd));
	return (0);
}

int	mini_echo(char *arg, char *flag)
{
	if (flag != NULL)
		printf("%s\n", arg);
	else
		printf("%s", arg);
	return (0);
}

int	mini_export(char *arg)
{
	(void)arg;
	return (0);
}
