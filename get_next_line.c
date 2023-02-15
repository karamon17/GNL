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
#define BUFFER_SIZE 3000
#endif

char	*get_next_line(int fd)
{
	char		*res;
	static char	*next;
	char		*nextnew;
	char		*freenext;
	char		*str;
	char		*search;
	char		tmp[2];
	int			i;

	i = 0;
	res = (char *)malloc(sizeof(char));
	if (!res)
		return (0);
	res[0] = 0;
	if (next)
	{
		nextnew = ft_strchr(next, '\n');
		if (nextnew)
		{
			*nextnew = 0;
			freenext = res;
			res = ft_strjoin(res, next);
			if (!res)
				return (0);
			if (freenext)
				free(freenext);
			next = nextnew + 1;
			if (ft_strlen(next) == 0)
				free(next - 1);
			return(res);
		}
		else
		{
			freenext = res;
			res = ft_strjoin(res, next);
			if (!res)
				return (0);
			if (freenext)
				free(freenext);
			next = 0;
		}
		//printf("%s\n", next);
	}
	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	i = read(fd, str, BUFFER_SIZE);
	str[i] = 0;
	search = ft_strchr(str, '\n');
	while (!search && BUFFER_SIZE == ft_strlen(str))
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
		search = ft_strchr(str, '\n');
	}
	i = 0;
	while(str[i] && str[i] != '\n')
	{
		tmp[0] = str[i];
		tmp[1] = 0;
		freenext = res;
		res = ft_strjoin(res, tmp);
		if (!res)
			return (0);
		if (freenext)
			free(freenext);
		i++;
	}
	i++;
	if (!next)
	{
		next = (char *)malloc(sizeof(char));
		if (!next)
			return (0);
		next[0] = 0;
		while(str[i])
		{
			tmp[0] = str[i];
			tmp[1] = 0;
			freenext = next;
			next = ft_strjoin(next, tmp);
			if (!next)
				return (0);
			if (freenext)
				free(freenext);
			i++;
		}
	}
	free(str);
	if (ft_strlen(next) == 0)
		free(next);
	//printf("test%s\n", next);
	return (res);
}

int main()
{
	int fd = open("README.md", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	//printf("%s\n", get_next_line(fd));
	close(fd);
}