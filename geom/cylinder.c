/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:19:17 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:14:10 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static t_ray_prop	check_limits(t_ray_prop props, t_solid obj,
									t_3dfvec orientation, t_3dfvec origin)
{
	t_3dfvec	diff;
	t_3dfvec	p1;
	t_3dfvec	p2;

	props.pos = vecadd_3dfvec(scalprod_3dfvec(props.dir, props.dist), origin);
	p1 = set_3dfvec(obj.points[0][0], obj.points[0][1], obj.points[0][2]);
	p2 = set_3dfvec(obj.points[1][0], obj.points[1][1], obj.points[1][2]);
	diff = vecmin_3dfvec(props.pos, p2);
	if (dotprod_3dfvec(orientation, diff) <= 0)
		props.dist = -1;
	diff = vecmin_3dfvec(props.pos, p1);
	if (dotprod_3dfvec(orientation, diff) >= 0)
		props.dist = -1;
	return (props);
}

static void	find_root(double *root1, double *root2, double *f)
{
	double	delta;
	double	res;

	delta = (f[1] * f[1]) - (4 * f[0] * f[2]);
	if (delta > 0)
	{
		if (f[1] > 0)
			res = -0.5 * (f[1] + sqrt(delta));
		else
			res = -0.5 * (f[1] - sqrt(delta));
		*root1 = res / f[0];
		*root2 = f[2] / res;
		if (*root1 < *root2)
			res = *root1;
		else
			res = *root2;
		if (res != *root1)
			*root2 = *root1;
		*root1 = res;
	}
	else if (!delta)
		*root1 = (-f[1] / (f[0] * 2));
}

static t_ray_prop	solve_quadratic(double *f, t_ray_prop props,
									t_solid obj, t_3dfvec *vec)
{
	double	root1;
	double	root2;

	root1 = -1;
	root2 = -1;
	find_root(&root1, &root2, f);
	if (root1 < 0 && root2 < 0)
		props.dist = -1;
	else if (root1 > 0)
	{
		props.dist = root1;
		props = check_limits(props, obj, vec[1], vec[0]);
		if (props.dist < 0 && root2 > 0)
		{
			props.dist = root2;
			props = check_limits(props, obj, vec[1], vec[0]);
		}
	}
	else
	{
		props.dist = root2;
		props = check_limits(props, obj, vec[1], vec[0]);
	}
	return (props);
}

static t_ray_prop	solve_cylinder(t_3dfvec *vec, double *d,
									t_ray_prop props, t_solid obj)
{
	double			f[3];
	t_3dfvec		tmp[2];
	double			m;
	t_3dfvec		scal;

	tmp[0] = vecmin_3dfvec(props.dir, scalprod_3dfvec(vec[1], d[0]));
	f[0] = dotprod_3dfvec(tmp[0], tmp[0]);
	tmp[1] = vecmin_3dfvec(vec[2], scalprod_3dfvec(vec[1], d[1]));
	f[1] = 2 * dotprod_3dfvec(tmp[0], tmp[1]);
	f[2] = dotprod_3dfvec(tmp[1], tmp[1]) - (obj.scale.x * obj.scale.x);
	props = solve_quadratic(f, props, obj, vec);
	if (props.dist < 0)
		return (props);
	props.normal = set_3dfvec(props.pos.x - obj.points[1][0],
			props.pos.y - obj.points[1][1],
			props.pos.z - obj.points[1][2]);
	m = dotprod_3dfvec(vec[1], props.normal);
	scal = scalprod_3dfvec(vec[1], m);
	props.normal = normalize_ray(vecmin_3dfvec(props.normal, scal));
	return (props);
}

t_ray_prop	intersect_cylinder(t_ray_prop props, t_3dfvec orig, t_solid obj)
{
	double		d[2];
	t_3dfvec	vec[3];

	vec[0] = orig;
	vec[1].x = obj.points[0][0] - obj.points[1][0];
	vec[1].y = obj.points[0][1] - obj.points[1][1];
	vec[1].z = obj.points[0][2] - obj.points[1][2];
	vec[1] = normalize_ray(vec[1]);
	vec[2].x = vec[0].x - obj.points[1][0];
	vec[2].y = vec[0].y - obj.points[1][1];
	vec[2].z = vec[0].z - obj.points[1][2];
	d[0] = dotprod_3dfvec(props.dir, vec[1]);
	d[1] = dotprod_3dfvec(vec[2], vec[1]);
	props = solve_cylinder(vec, d, props, obj);
	if (props.dist < 0)
		return (props);
	props.inters = obj;
	return (props);
}
