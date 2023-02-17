/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:40:56 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/02/13 18:40:58 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !s2)
		return (0);
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (0);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	c1;

	c1 = c;
	while (*s && c1 != *s)
		s++;
	if (c1 == *s)
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*str;
	int		i;

	len = ft_strlen(s1) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		((unsigned char *)str)[i] = ((unsigned char *)s1)[i];
		i++;
	}
	return (str);
}