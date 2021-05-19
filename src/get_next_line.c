#include "get_next_line.h"
#include <unistd.h>

void	search_for_fd(t_gnl_list *list, int fd)
{
	t_gnl_list	*node;

	if (list->next->fd == fd)
	{
		node = list->next;
		list->next = list->next->next;
		free(node->buf);
		free(node);
	}
	else
		search_for_fd(list->next, fd);
}

void	free_node(t_gnl_list **head, int fd)
{
	t_gnl_list	*node;

	node = *head;
	if (node->fd == fd)
	{
		*head = node->next;
		free(node->buf);
		free(node);
	}
	else
		search_for_fd(node, fd);
}

t_gnl_list	*buf_check(t_gnl_list **head, int fd)
{
	t_gnl_list	*node_ptr;
	t_gnl_list	*new_node;

	node_ptr = *head;
	while (node_ptr)
	{
		if (node_ptr->fd == fd)
			return (node_ptr);
		node_ptr = node_ptr->next;
	}
	new_node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (new_node == NULL)
		return (NULL);
	new_node->buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (new_node->buf == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->fd = fd;
	new_node->read_bytes = 0;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

int	read_from_fd(t_gnl_list *b_node, char **buf)
{
	ssize_t	r_bytes;
	size_t	nl;

	if (b_node->read_bytes == 0)
	{
		r_bytes = read(b_node->fd, b_node->buf, BUFFER_SIZE);
		if (r_bytes == -1 || r_bytes == 0)
			return (r_bytes);
		b_node->buf[r_bytes] = '\0';
		b_node->read_bytes = r_bytes;
	}
	nl = find_char(b_node->buf, '\n');
	*buf = concat_buffer(*buf, b_node->buf, nl);
	if (*buf == NULL)
		return (-1);
	if (nl < b_node->read_bytes)
	{
		b_node->read_bytes = b_node->read_bytes - nl - 1;
		copy_string(b_node->buf, b_node->buf + nl + 1, b_node->read_bytes);
		return (1);
	}
	else
		b_node->read_bytes = 0;
	return (42);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl_list	*b_list;
	t_gnl_list			*b_node;
	char				*buf;
	int					ret;

	ret = 42;
	b_node = buf_check(&b_list, fd);
	if (b_node == NULL)
		return (-1);
	buf = NULL;
	while (ret == 42)
		ret = read_from_fd(b_node, &buf);
	if (ret == 1)
		*line = buf;
	if (ret == 0)
	{
		*line = concat_buffer(buf, "", 0);
		free_node(&b_list, fd);
		if (*line == NULL)
			return (-1);
	}
	if (ret == -1)
		free_node(&b_list, fd);
	return (ret);
}
