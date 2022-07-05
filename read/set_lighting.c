/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lighting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:55:48 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 14:56:56 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include "../includes/calc.h"
#include "../includes/geom.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	check_ambient(t_light *lights)
{
	while (lights)
	{
		if (lights->type == 'a')
		{
			ft_putstr_fd(2, "Error\nOnly one ambient light can be defined\n");
			return (1);
		}
		lights = lights->next;
	}
	return (0);
}

t_light	*set_lighting(char type, char *line, t_light *lights)
{
	int			*color;
	t_3dfvec	*vec;
	double		intens;
	t_light		*new;

	line += 2;
	vec = (void *)0;
	if (type != 'A')
		vec = get_fvals(&line);
	intens = get_fval(&line);
	color = get_col(&line);
	if ((type != 'A' && !vec) || intens == -1 || !color)
		return ((void *)0);
	if (type == 'A' && !(check_ambient(lights)))
		new = set_light('a', set_3dfvec(0, 0, 0), intens);
	else if (type == 'l')
		new = set_light('p', *vec, intens * 100);
	else if (type == 'd')
		new = set_light('d', normalize_ray(*vec), intens * 10);
	else
		new = (void *)0;
	new = complete_light(new, *color, lights);
	free(color);
	free(vec);
	return (new);
}
