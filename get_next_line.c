/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhaishb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:40:44 by gkhaishb          #+#    #+#             */
/*   Updated: 2023/02/13 18:40:46 by gkhaishb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef	BUFFER_SIZE
#define BUFFER_SIZE 10000
#endif

static void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static char *ft_checknext(char **next, char **res)
{
	char	*p_n;
	char	*frres;

	p_n = 0;
	if (*next)
	{
		if ((p_n = ft_strchr(*next, '\n')))
		{
			*p_n = 0;
			frres = *res;
			*res = ft_strdup(*next);
			if (!(*res))
				return (0);
			free(frres);
			*res = ft_strjoin(*res, "\n");
			if (!(*res))
				return (0);
			p_n++;
			ft_strcpy(*next, p_n);
		}
		else
		{
			*res = ft_strdup(*next);
			if (!(*res))
				return (0);
			free(*next);
			*next = 0;
		}
	}
	else
	{	
		*res = ft_calloc(1, 1);
		if (!(*res))
			return (0);
	}
	return (p_n);
}

char	*get_next_line(int fd)
{
	char static	*next;
	char		*res;
	char		*str;
	char		*p_n;
	int			read_bites;

	if (fd < 0)
		return (0);
	res = 0;
	p_n = ft_checknext(&next, &res);
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	while(!p_n && (read_bites = read(fd, str, BUFFER_SIZE))  > 0)
	{
		str[read_bites] = 0;
		if ((p_n = ft_strchr(str, '\n')))
		{
			*p_n = 0;
			p_n++;
			
			next = ft_strdup(p_n);
			if (!next)
				return (0);
			res = ft_strjoin(res, str);
			if (!res)
				return (0);
			res = ft_strjoin(res, "\n");
			if (!res)
				return (0);
		}
		else
		{
			res = ft_strjoin(res, str);
			if (!res)
				return (0);
		}
	}
	free(str);
	if (res[0] == 0)
		return (0);
	return (res);
}

/*int main()
{
	int fd = open("README.md", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
}*/