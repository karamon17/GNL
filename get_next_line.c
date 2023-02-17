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
#define BUFFER_SIZE 1
#endif

char	*get_next_line(int fd)
{
	char		*res;
	static char	*next;
	static int	count;
	char		*nextnew;
	char		*freenext;
	char		*str;
	char		*strlast;
	char		tmp;
	int			i;

	if (fd < 0)
		return (0);
	res = (char *)malloc(sizeof(char));
	if (!res)
		return (0);
	res[0] = 0;
	if (next)
	{
		nextnew = ft_strchr(next, '\n');
		if (nextnew)
		{
			tmp = nextnew[1];
			nextnew[1] = 0;
			res = ft_strjoin("\0", next);
			if (!res)
				return (0);
			nextnew[1] = tmp;
			next = nextnew + 1;
			return(res);
		}
		else
		{
			res = ft_strjoin("\0", next);
			if (!res)
				return (0);
			free(next);
		}
	}
	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	i = read(fd, str, BUFFER_SIZE);
	if (i == 0 && count == 0)
	{
		free(str);
		count = 1;
		return (res);
	}
	else if (i == 0 && count == 1)
	{
		free(str);
		free(res);
		return (0);
	}
	str[i] = 0;
	while (!ft_strchr(str, '\n') && BUFFER_SIZE == ft_strlen(str))
	{
		freenext = res;
		res = ft_strjoin(res, str);
		if (!res)
			return (0);
		if (freenext)
			free(freenext);
		i = read(fd, str, BUFFER_SIZE);
		if (!i)
			return (res);
		str[i] = 0;
	}
	if (ft_strchr(str, '\n'))
	{
		strlast = str;
		str = ft_strchr(str, '\n');
		tmp = str[1];
		str[1] = 0;
		freenext = res;
		res = ft_strjoin(res, strlast);
		if (!res)
			return (0);
		free(freenext);
		str[1] = tmp;
		str++;
	}
	else
	{
		freenext = res;
		res = ft_strjoin(res, str);
		if (!res)
			return (0);
		free(freenext);
	}
	if (!next)
	{
		next = ft_strdup(str);
		if (!next)
			return (0);
	}
	free(strlast);
	return (res);
}

/*int main()
{
	int fd = open("README.md", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
}*/