#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	exit_minishell(int error_id)
{
	printf("Error: %s [%d]\n", strerror(error_id), error_id);
	printf("Exiting minishell...\n");
	exit(error_id);
}

void	exit_minishell_custom(char *str)
{
	printf("%s\n", str);
	printf("Exiting minishell...\n");
	exit(1);
}
