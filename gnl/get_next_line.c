/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:41:05 by troxanna          #+#    #+#             */
/*   Updated: 2020/12/11 18:56:08 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_free(char *str)
{
	if (str)
		free(str);
	return (-1);
}

char				*remainder_update(char *ptr, char *remainder)
{
	char			*str;
	int				i;

	i = 0;
	if (ptr)
	{
		str = (char *)malloc((ft_strlen(ptr) + 1) * sizeof(char));
		if (str)
		{
			while (ptr[i] != '\0')
			{
				str[i] = ptr[i];
				i++;
			}
			str[i] = '\0';
			free(remainder);
			return (str);
		}
	}
	return (NULL);
}

char				*check_remainder(char *remainder, char **line)
{
	char			*ptr_n;

	if (remainder)
	{
		if ((ptr_n = ft_strchr(remainder, '\n')))
		{
			*ptr_n = '\0';
			*line = ft_strdup(remainder);
			remainder = remainder_update(++ptr_n, remainder);
			return (remainder);
		}
		else
		{
			*line = ft_strdup(remainder);
			free(remainder);
		}
	}
	else
		*line = ft_strdup("");
	return (NULL);
}

int					get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*remainder;
	char			*ptr_n;
	int				read_c_b;

	buff = NULL;
	if (line == NULL || BUFFER_SIZE <= 0 ||
		(!(buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		|| (read_c_b = read(fd, buff, 0)) < 0)
		return (buff ? ft_free(buff) : -1);
	*line = NULL;
	remainder = check_remainder(remainder, line);
	read_c_b = 1;
	while (!remainder && (read_c_b = read(fd, buff, BUFFER_SIZE)))
	{
		buff[read_c_b] = '\0';
		if ((ptr_n = ft_strchr(buff, '\n')))
		{
			*ptr_n = '\0';
			remainder = ft_strdup(++ptr_n);
		}
		*line = ft_strjoin(*line, buff);
	}
	free(buff);
	if (remainder)
		free(remainder);
	return (!read_c_b ? 0 : 1);
}
