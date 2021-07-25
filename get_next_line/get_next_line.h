/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:06:46 by kshanti           #+#    #+#             */
/*   Updated: 2021/07/01 19:00:58 by kshanti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "unistd.h"
# include "stdlib.h"
# include "fcntl.h"
# include "../includes/pipex.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

int			check_line(char **static_buff, char **line);
int			get_next_line(int fd, char **line);
char		*create_buff(char **buf);
int			create_reminder(int *res, char **static_buff, char **line);

#endif
