#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	sig_quit(int ig)
{
	(void)ig;
	signal(SIGINT, print_pr);
	signal(SIGQUIT, sig_quit);
	if (g_sig == 0)
	{
		rl_replace_line("", 0);
		ft_putchar('\n');
		rl_on_new_line();
		rl_redisplay();
	}
}

void	print_pr(int ig)
{
	(void)ig;
	signal(SIGINT, print_pr);
	signal(SIGQUIT, sig_quit);
	if (g_sig == 0)
	{
		rl_replace_line("", 0);
		ft_putchar('\n');
		rl_on_new_line();
		rl_redisplay();
	}
}

void	incrment_global_sig(void)
{
	g_sig++;
}

void	decrement_global_sig(void)
{
	g_sig--;
}
