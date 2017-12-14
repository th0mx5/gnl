/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbernar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 12:57:35 by thbernar          #+#    #+#             */
/*   Updated: 2017/12/14 15:35:25 by thbernar         ###   ########.fr       */
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

static int	ft_read_fd(const int fd, char **s)
{
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = 0;
		tmp = *s;
		*s = ft_strjoin(*s, buff);
		free(tmp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret == -1)
		return (-1);
	if (ret == 0 && *s[0] == '\0')
		return (0);
	tmp = *s;
	if (!(*s = ft_strsub(*s, 0, ft_strlen(*s))))
		return (-1);
	free(tmp);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*s;
	char		*tmp;
	int			ret;
	int			f_endline;

	if (fd < 0 || line == NULL)
		return (-1);
	if (s == NULL)
		s = ft_strnew(1);
	if ((ret = ft_read_fd(fd, &s)) == -1)
		return (-1);
	f_endline = ft_strclen(s, '\n');
	if (!(*line = ft_strsub(s, 0, f_endline)))
		return (-1);
	tmp = s;
	if (!(s = ft_strsub(s, f_endline + 1, ft_strlen(s) - f_endline)))
		return (-1);
	free(tmp);
	return (ret);
}
