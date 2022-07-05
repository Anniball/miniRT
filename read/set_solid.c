/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_solid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 11:53:30 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/21 15:08:12 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/read.h"
#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/main.h"
#include "../includes/bonus.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static t_3dfvec	ptr_to_3dfvec(t_3dfvec *ptr)
{
	t_3dfvec	vec;

	vec = *ptr;
	free(ptr);
	return (vec);
}

static t_solid	*t_type(char *line, t_solid *objs)
{
	t_3dfvec	points[3];
	t_material	*mat;
	t_solid		*tmp;
	t_3dfvec	*p[3];

	tmp = (void *)0;
	p[0] = get_fvals(&line);
	p[1] = get_fvals(&line);
	p[2] = get_fvals(&line);
	mat = check_mat(&line);
	if (p[0] && p[1] && p[2] && mat)
	{
		points[0] = ptr_to_3dfvec(p[0]);
		points[1] = ptr_to_3dfvec(p[1]);
		points[2] = ptr_to_3dfvec(p[2]);
		tmp = set_triangle(set_trans(set_3dfvec(0, 0, 0), set_3dfvec(0, 0, 0),
					set_3dfvec(1, 1, 1)), points, objs, mat);
	}
	return (tmp);
}

static t_solid	*c_type(char *line, t_solid *objs)
{
	t_3dfvec	*pos;
	t_3dfvec	*rot;
	t_3dfvec	s;
	t_solid		*tmp;
	t_material	*mat;

	mat = (void *)0;
	tmp = (void *)0;
	pos = get_fvals(&line);
	rot = get_fvals(&line);
	if (pos && rot)
	{
		mat = check_mat(&line);
		s.x = get_fval(&line);
		s.y = get_fval(&line);
		if (interval_3dfvec(*rot, -1.0, 1.0) && mat
			&& s.x != -1.0 && s.y != -1.0)
		{
			*rot = scalprod_3dfvec(*rot, M_PI * 2);
			tmp = set_cylinder(set_trans(*pos, *rot, s), objs, mat, s);
		}
	}
	free(pos);
	free(rot);
	return (tmp);
}

static t_solid	*o_types(char type, char *line, t_solid *objs, t_3dfvec **t)
{
	t_3dfvec	s;
	t_solid		*tmp;
	t_material	*mat;

	s = set_3dfvec(1, 1, 1);
	mat = (void *)0;
	tmp = (void *)0;
	if (((type != 's' && interval_3dfvec(*(t[1]), -1.0, 1.0)) || (type == 's'))
		&& !((type == 's' || type == 'q') && ((s.x = get_fval(&line)) == -1.0))
		&& (mat = check_mat(&line)))
	{
		if (type != 's')
			*(t[1]) = scalprod_3dfvec(*(t[1]), M_PI * 2);
		if (type == 's')
			tmp = set_sphere(set_trans(*(t[0]), set_3dfvec(0, 0, 0), s),
					objs, mat);
		else if (type == 'q')
			tmp = set_quad(set_trans(*(t[0]), *(t[1]), s),
					objs, mat);
		else if (type == 'p')
			tmp = set_plane(set_trans(*(t[0]), *(t[1]), set_3dfvec(1, 1, 1)),
					objs, mat);
	}
	return (tmp);
}

t_solid	*set_solid(char type, char *line, t_solid *objs)
{
	t_3dfvec	*t[2];
	t_solid		*tmp;

	t[0] = (void *)0;
	t[1] = (void *)0;
	tmp = (void *)0;
	line += 2;
	if (type == 't')
		tmp = t_type(line, objs);
	else if (type == 'c')
		tmp = c_type(line, objs);
	else
	{
		t[0] = get_fvals(&line);
		if (type != 's')
			t[1] = get_fvals(&line);
		if (!(!(t[0]) || (type != 's' && !(t[1]))))
			tmp = o_types(type, line, objs, t);
	}
	free(t[0]);
	free(t[1]);
	return (tmp);
}
