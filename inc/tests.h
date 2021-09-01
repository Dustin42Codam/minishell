#ifndef TESTS_H
# define TESTS_H
# ifndef malloc
int	g_malloc_cnt;
# include <stdlib.h>
# define malloc(x) (g_malloc_cnt++ == MALLOC_COUNT ? ((void*)0) : malloc(x))
# endif
#endif
