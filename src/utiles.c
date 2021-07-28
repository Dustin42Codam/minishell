#include <stddef.h>

size_t	get_size_of_tokens(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ft_size_of_digit(int row)
{
	int	size;

	size = 0;
	while (row >= 10)
	{
		row = row / 10;
		size++;
	}
	return (size);
}
