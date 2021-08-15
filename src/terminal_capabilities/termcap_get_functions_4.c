#include "libft.h"

int	get_curent_row(char *buf)
{
	return (ft_atoi(buf + 2) - 1);
}

int	get_curent_col(char *buf, int row)
{
	return (ft_atoi(buf + 4
			+ (row >= 9)
			+ (row >= 99)) - 1);
}
