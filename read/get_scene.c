/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:43:16 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/21 12:01:04 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include "../includes/bonus.h"
#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/main.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	get_type(char *ln, t_solid **o, t_light **lights,
												t_camera **cam)
{
	t_solid		*tmp_o;
	t_light		*tmp_l;
	t_camera	*tmp_c;
	int			flag;

	tmp_o = *o;
	tmp_l = *lights;
	tmp_c = *cam;
	flag = set_objs(ln, o, lights, cam);
	if (!(*o))
		*o = tmp_o;
	else if (!(*lights))
		*lights = tmp_l;
	else if (!(*cam))
		*cam = tmp_c;
	return (flag);
}

static int	set_res(char *line, t_2dvec *res)
{
	line += 2;
	if (res->x != 0 || res->y != 0)
	{
		ft_putstr_fd(2, "Error\nResolution can't be defined twice.\n");
		return (-1);
	}
	res->x = get_val(&line);
	res->y = get_val(&line);
	if (res->x <= 0 || res->y <= 0)
	{
		ft_putstr_fd(2, "Error\nScreen size should always be superior to 0.\n");
		return (-1);
	}
	if (*line != '\0')
	{
		ft_putstr_fd(2, "Error\nOnly resolution should be put on 'R' line.\n");
		return (-1);
	}
	else
		return (0);
}

static t_param	*read_line(t_2dvec *res, t_param *par, char *line)
{
	if (!line)
	{
		ft_putstr_fd(2, "Error\nEmpty file or wrong filename. End.\n");
		free(line);
		return ((void *)0);
	}
	else if ((*line) && ((*line == 'R' && (set_res(line, res) == -1))
			|| (*line != 'R'
				&& (get_type(line, &(par->objs),
						&(par->lights), &(par->cams)) == -1))))
	{
		free(line);
		free_objects(par->objs, par->lights, par->cams);
		free(par->sky_name);
		free(par);
		return ((void *)0);
	}
	else
		free(line);
	return (par);
}

static int	open_file(char *filename, t_param *par)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(2, "Error\nFile couldn't be found.\n");
		free(par);
	}
	else
		ft_putstr_fd(1, "File opened.\n");
	return (fd);
}

t_param	*read_file(char *filename, t_2dvec *res, t_param *par)
{
	char		*line;
	int			fd;
	int			read;

	read = 1;
	*res = set_2dvec(0, 0);
	fd = open_file(filename, par);
	if (fd == -1)
		return ((void *)0);
	while (read)
	{
		read = get_next_line(fd, &line);
		if ((BONUS == 1 && !(get_bonus(line, par))) || BONUS == 0)
		{
			par = read_line(res, par, line);
			if (!par)
				break ;
		}
	}
	close(fd);
	ft_putstr_fd(1, "File read.\n");
	return (par);
}
