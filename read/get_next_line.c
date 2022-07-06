/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:14:44 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/06 15:34:05 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"

static int	get_line(char **line, char *str, char c)
{
	int		i;
	int		j;
	char	*new_line;

	if (!line || !*line || !str)
		return (-1);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	new_line = malloc(sizeof(*new_line) * (i + ft_strlen(*line) + 1));
	if (!new_line)
		return (-1);
	i = -1;
	while ((*line)[++i])
		new_line[i] = ((*line)[i]);
	j = -1;
	while (str[++j] && str[j] != c)
		new_line[i + j] = str[j];
	new_line[i + j] = '\0';
	free(*line);
	*line = new_line;
	return (j);
}

static int	get_rest_line(char **rest, char **line, char c, char *buf)
{
	int		j;
	char	*new_rest;
	char	*tmp;

	if (!buf)
		tmp = *rest;
	else
		tmp = buf;
	j = get_line(line, tmp, c);
	if (j == -1)
		return (-1);
	if (!tmp[j])
	{
		free(*rest);
		*rest = (void *)0;
		return (0);
	}
	new_rest = ft_strdup(tmp + j + 1);
	if (!new_rest)
		return (-1);
	free(*rest);
	*rest = new_rest;
	return (0);
}

static int	finish_gnl(char *str1, char *str2, int ret)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			*buf;
	static char		*rest = (void *)0;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(*buf));
	if (!buf)
		return (-1);
	if ((!line || fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		|| (!(*line = ft_strdup("\0"))))
		return (finish_gnl(buf, (void *)0, -1));
	if (rest && (get_rest_line(&rest, line, '\n', (void *)0)) == -1)
		return (finish_gnl(buf, *line, -1));
	ret = BUFFER_SIZE;
	while (ret && !rest)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (finish_gnl(buf, *line, -1));
		buf[ret] = '\0';
		if (get_rest_line(&rest, line, '\n', buf) == -1)
			return (finish_gnl(buf, *line, -1));
	}
	if (ret)
		return (finish_gnl(buf, (void *)0, 1));
	return (finish_gnl(buf, (void *)0, 0));
}
