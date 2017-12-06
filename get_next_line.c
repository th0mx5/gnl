/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 12:57:35 by thbernar          #+#    #+#             */
/*   Updated: 2017/12/06 16:04:43 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>

void	ft_read_fd(const int fd, char **s);
void	ft_get_line_n(char **s, char **line, int n);

int		get_next_line(const int fd, char **line)
{
	static int n;
	static char **tab;
	char *s;
	s = (char*)malloc(sizeof(s));
	ft_read_fd(fd, &s);
	s = ft_strsplit(s, '\n')[2];
	ft_strcpy(*line, s);
	free(s);
	n++;
	return (0);
}

void	ft_read_fd(const int fd, char **s)
{
	char buff[BUFF_SIZE + 1];
	int ret;
	char *p_s;

	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		p_s = *s;
		buff[ret] = 0;
		*s = ft_strjoin(*s, buff);
		free(p_s);
	}
}

int main (void)
{
	int fd;
	char s[1024];
	char *p_s;

	p_s = s;
	fd = open("sample", O_RDONLY);
	if (fd == -1)
		return (-1);
	get_next_line((const int)fd, &p_s);
	ft_putstr(p_s);
	get_next_line((const int)fd, &p_s);
	ft_putstr(p_s);
	return (0);
}
