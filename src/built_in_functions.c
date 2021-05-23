#include <limits.h>
#include <unistd.h>
#include <stdio.h>

#include "libft.h"

int	cd()
{
	
	return (0);
}

/*
**	The pwd utility exits 0 on success, and >0 if an error occurs
*/

int	pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (-1);
	}
	else
		ft_putstr(cwd);
	return (0);
}
