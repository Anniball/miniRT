/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:11:28 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:54:36 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/main.h"
#include "../includes/bonus.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static double	solve_quadratic(double a, double b, double c)
{
	double	delta;
	double	res;
	double	root1;
	double	root2;

	delta = (b * b) - (4 * a * c);
	if (delta > 0)
	{
		if (b > 0)
			res = -0.5 * (b + sqrt(delta));
		else
			res = -0.5 * (b - sqrt(delta));
		root1 = res / a;
		root2 = c / res;
		if (root1 < 0)
			return (root2);
		if (root2 < 0)
			return (root1);
		if (root1 < root2)
			return (root1);
		return (root2);
	}
	else if (!delta)
		return (-b / (a * 2));
	return (-1);
}

t_ray_prop	intersect_sphere(t_ray_prop props, t_3dfvec origin, t_solid obj)
{
	t_3dfvec	local;
	double		b;
	double		c;

	local = set_3dfvec(origin.x - obj.trans[3][0],
			origin.y - obj.trans[3][1], origin.z - obj.trans[3][2]);
	b = 2 * dotprod_3dfvec(props.dir, local);
	c = dotprod_3dfvec(local, local) - (obj.trans[0][0] * obj.trans[0][0]);
	props.dist = (solve_quadratic(1, b, c));
	if (props.dist >= 0)
	{
		props.pos.x = origin.x + (props.dist * props.dir.x);
		props.pos.y = origin.y + (props.dist * props.dir.y);
		props.pos.z = origin.z + (props.dist * props.dir.z);
		props.normal = set_3dfvec(obj.trans[3][0], obj.trans[3][1],
				obj.trans[3][2]);
		props.normal = vecmin_3dfvec(props.normal, props.pos);
		props.normal = normalize_ray(props.normal);
		props.inters = obj;
	}
	return (props);
}

t_solid	*set_sphere(double **trans, t_solid *next, t_material *mat)
{
	t_solid	*sphere;

	sphere = malloc(sizeof(*sphere));
	if (!sphere)
		return ((void *)0);
	sphere->type = 's';
	sphere->trans = trans;
	sphere->points = (void *)0;
	sphere->sides = (void *)0;
	sphere->next = next;
	sphere->mat = mat;
	return (sphere);
}
