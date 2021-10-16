/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_control.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkrecisz <dkrecisz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/15 11:05:43 by dkrecisz      #+#    #+#                 */
/*   Updated: 2021/10/15 14:15:32 by dkrecisz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "structs.h"
# include <sys/types.h>

void	job_add(t_data *data, pid_t pid, t_command *cmd);

#endif
