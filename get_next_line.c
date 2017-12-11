/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 12:57:35 by thbernar          #+#    #+#             */
/*   Updated: 2017/12/11 17:36:07 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>

static int	ft_read_fd(const int fd, char **s)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	char	*p_s;

	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		p_s = *s;
		buff[ret] = 0;
		*s = ft_strjoin(*s, buff);
		free(p_s);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static int	n;
	static char **tab;
	char		*s;
	int			i;

	i = 0;
	if (fd < 0)
		return (-1);
	if (n == 0)
	{
		s = (char*)malloc(sizeof(s));
		if (ft_read_fd(fd, &s) == -1)
			return (-1);
		if (s[0] == '\0' || (s[0] == '\n' && s[1] == '\0'))
			return (0);
		tab = ft_strsplit(s, '\n');
		ft_strcpy(*line, tab[n]);
		free(s);
	}
	else if (n != 0 && tab[n] == 0)
		return (0);
	ft_strcpy(*line, tab[n]);
	n++;
	return (1);
}

int			main(void)
{
	int		fd;
	char	str[1024];
	char	*s;
	int		ret;

	ret = 0;
	s = str;
	fd = open("sample", O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((ret = get_next_line((const int)fd, &s) > 0))
	{
		printf("ret = %d, s = %s\n", ret, s);
	}
	return (0);
}
