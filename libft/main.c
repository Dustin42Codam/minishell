#include "libft.h"
#include <limits.h>
#include <stdlib.h>

int	main(void)
{
	char	*s0 = ft_itoa(0);
	char	*s1 = ft_itoa(INT_MIN);
	char	*s2 = ft_itoa(INT_MAX);
	char	*s4 = ft_strdup("lol");
	char	*s5 = ft_strdup("");
	char	*s6 = ft_strjoin("abc", "d");
	char	*s7 = ft_strjoin("abc", "");
	char	*s8 = ft_strjoin("", "abc");
	char	*s9 = ft_strtrim("123abc123", "123");
	char	*s10 = ft_substr("abcd", 0, 2);


	free(s0);
	free(s1);
	free(s2);
	free(s4);
	free(s5);
	free(s6);
	free(s7);
	free(s8);
	free(s9);
	free(s10);
	return (0);
}
