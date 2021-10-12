/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_putstr_fd.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkrusts/dkrecisz <codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 15:57:16 by alkrusts/dk   #+#    #+#                 */
/*   Updated: 2021/09/13 15:57:40 by alkrusts/dk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

ssize_t	minishell_putstr_fd(const char *str, int fd)
{
	return (minishell_write(fd, str, ft_strlen(str)));
}
