/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:05:13 by troxanna          #+#    #+#             */
/*   Updated: 2020/12/12 14:48:23 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t			ft_strlen(char *str)
// {
// 	size_t	c;

// 	c = 0;
// 	if (str)
// 	{
// 		while (str[c] != '\0')
// 			c++;
// 	}
// 	return (c);
// }

static char		*ft_strjoin_fill_in(char *s1, char *s2, size_t len)
{
	char		*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

// char			*ft_strjoin(char *s1, char *s2)
// {
// 	size_t	len;
// 	char	*str;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	str = ft_strjoin_fill_in(s1, s2, len);
// 	free(s1);
// 	return (str);
// }

// char			*ft_strchr(char *str, int c)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return ((char *)str + i);
// 		else
// 			i++;
// 	}
// 	if (str[i] == c)
// 		return ((char *)str + i);
// 	return (NULL);
// }

// char			*ft_strdup(char *str)
// {
// 	char	*ptr;
// 	int		i;

// 	i = 0;
// 	ptr = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
// 	if (ptr)
// 	{
// 		while (str[i] != '\0')
// 		{
// 			ptr[i] = str[i];
// 			i++;
// 		}
// 		ptr[i] = '\0';
// 		return (ptr);
// 	}
// 	else
// 		return (NULL);
// }
