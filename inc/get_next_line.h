/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 18:29:12 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/05/19 15:07:06 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stdlib.h>

typedef struct s_gnl_list
{
	int					fd;
	char				*buf;
	size_t				read_bytes;
	struct s_gnl_list	*next;
}	t_gnl_list;

int					get_next_line(int fd, char **line);
char				*concat_buffer(char *prefix, char *buf, size_t len);
char				*copy_string(char *dst, const char *src, size_t len);
size_t				find_char(char *haystack, char needle);

#endif
