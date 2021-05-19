#include "get_next_line.h"

char	*concat_buffer(char *prefix, char *suffix, size_t len)
{
	size_t	prefix_len;
	char	*new;

	if (prefix == NULL)
	{
		new = (char *)malloc(sizeof(char) * len + 1);
		if (new == NULL)
			return (NULL);
		copy_string(new, suffix, len);
	}
	else
	{
		prefix_len = find_char(prefix, '\0');
		new = (char *)malloc(sizeof(char) * (prefix_len + len + 1));
		if (new == NULL)
			return (NULL);
		copy_string(new, prefix, prefix_len);
		free(prefix);
		copy_string(new + prefix_len, suffix, len);
	}
	return (new);
}

char	*copy_string(char *dst, const char *src, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

size_t	find_char(char *haystack, char needle)
{
	size_t	index;

	index = 0;
	while (haystack[index])
	{
		if (haystack[index] == needle)
			return (index);
		index++;
	}
	return (index);
}
