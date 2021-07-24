/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:25:54 by troxanna          #+#    #+#             */
/*   Updated: 2020/12/11 18:53:49 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../includes/pipex.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

int		get_next_line(int fd, char **line);
char	*check_remainder(char *remainder, char **line);
char	*remainder_update(char *ptr, char *remainder);
int		ft_free(char *str);
// size_t	ft_strlen(char *str);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strchr(char *str, int c);
// char	*ft_strdup(char *str);

#endif
