#include "libft.h"
#include <stdlib.h>
#include <errno.h>

static size_t	get_arr_size(char const *s, const char *delim)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		if (!ft_strchr(delim, *s) && (ft_strchr(delim, *(s + 1)) || \
			*(s + 1) == '\0'))
			size++;
		s++;
	}
	return (size);
}

static size_t	get_token_size(char const *s, const char *delim)
{
	size_t	i;
	size_t	j;
	char	*scope;

	scope = NULL;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (delim[j])
		{
			if (s[i] == delim[j])
			{
				scope = (char *)s + i;
				return (scope - s);
			}
			j++;
		}
		i++;
	}
	if (scope == NULL)
		scope = (char *)s + ft_strlen(s);
	return (scope - s);
}

static void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	make_tokens(char **arr, const char *s, const char *delim)
{
	size_t	token_size;
	size_t	s_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	s_len = ft_strlen(s);
	while (i < s_len)
	{
		while (ft_strchr(delim, s[i]))
			i++;
		if (i >= s_len)
			break ;
		token_size = get_token_size(s + i, delim);
		arr[j] = ft_substr(s + i, 0, token_size);
		if (arr[j] == NULL)
			return (1);
		j++;
		i += token_size;
	}
	arr[j] = NULL;
	return (0);
}

char	**tokenizer(char const *s, const char *delim)
{
	char		**arr;
	size_t		size;

	if (s == NULL)
		return (NULL);
	if (!delim)
		delim = "";
	size = get_arr_size(s, delim);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (arr == NULL)
		return (NULL);
	if (make_tokens(arr, s, delim) == 1)
		free_arr(arr);
	return (arr);
}
