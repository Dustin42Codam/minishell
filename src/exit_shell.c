#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	exit_shell(int error_id)
{
	printf("Error: %s [%d]\n", strerror(error_id), error_id);
	printf("Exiting minishell...\n");
	exit(error_id);
}
