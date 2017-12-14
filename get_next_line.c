/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 12:57:35 by thbernar          #+#    #+#             */
/*   Updated: 2017/12/14 14:16:29 by thbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>

static int	ft_strclen(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_read_fd(const int fd, char **tmp_line)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		*tmp_line = ft_strjoin(*tmp_line, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && *tmp_line[0] == '\0')
		return (0);
	*tmp_line = ft_strsub(*tmp_line, 0, ft_strlen(*tmp_line));
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*s;
	int			ret;
	int			f_endline;

	if (fd < 0 || line == NULL)
		return (-1);
	if (s == NULL)
	{
		s = ft_strnew(1);
		ret = ft_read_fd(fd, &s);
		f_endline = ft_strclen(s, '\n');
		*line = ft_strsub(s, 0, f_endline);
		s = ft_strsub(s, f_endline + 1, ft_strlen(s) - f_endline);
	}
	else
	{
		ret = ft_read_fd(fd, &s);
		f_endline = ft_strclen(s, '\n');
		*line = ft_strsub(s, 0, f_endline);
		s = ft_strsub(s, f_endline + 1, ft_strlen(s) - f_endline);
	}
	return (ret);
}

/*int			main(void)
{
	int		fd;
	char	*s;
	int		ret;

	ret = 0;
	fd = open("sample", O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((ret = get_next_line((const int)fd, &s) > 0))
		printf("ret = %d, s = %s\n", ret, s);
	printf("ret = %d, s = %s\n", ret, s);
	return (0);
}*/
