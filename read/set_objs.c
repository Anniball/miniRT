/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:02:46 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/05 13:18:58 by ldelmas          ###   ########.fr       */
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

static int	check_init(char *ln, t_solid **o)
{
	int	ret;

	ret = 0;
	if (*ln == 's' && *(ln + 1) == 'p')
		*o = set_solid('s', ln, *o);
	else if (*ln == 'p' && *(ln + 1) == 'l')
		*o = set_solid('p', ln, *o);
	else if (*ln == 's' && *(ln + 1) == 'q')
		*o = set_solid('q', ln, *o);
	else if (*ln == 'c' && *(ln + 1) == 'y')
		*o = set_solid('c', ln, *o);
	else if (*ln == 't' && *(ln + 1) == 'r')
		*o = set_solid('t', ln, *o);
	else
		ret = -1;
	if (ret == -1 || !(*o))
	{
		ft_putstr_fd(2, "Error\nBad char at line's start or bad settings.\n");
		return (-1);
	}
	return (0);
}

int	set_objs(char *ln, t_solid **o, t_light **lights, t_camera **cam)
{
	t_solid		*o_o;
	t_light		*o_l;
	t_camera	*o_c;

	o_o = *o;
	o_l = *lights;
	o_c = *cam;
	if (*ln == 'A' || *ln == 'l' || *ln == 'd')
		*lights = set_lighting(*ln, ln, *lights);
	else if (*ln == 'c' && *(ln + 1) != 'y')
		*cam = set_cam(ln, *cam);
	else
		return (check_init(ln, o));
	if (((*ln == 'A' || *ln == 'l' || *ln == 'd') && *lights)
		|| ((*ln == 'c' && *(ln + 1) != 'y') && *cam))
		return (0);
	if (!(*o))
		*o = o_o;
	if (!(*lights))
		*lights = o_l;
	if (!(*cam))
		*cam = o_c;
	ft_putstr_fd(2, ln);
	write(2, "\n", 2);
	ft_putstr_fd(2, "Error\nBad char at line's start or bad settings.\n");
	return (-1);
}
