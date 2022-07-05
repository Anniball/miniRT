/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:41:20 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/19 15:08:26 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/calc.h"
#include "../includes/geom.h"

t_2dfvec	uv_sphere(t_3dfvec n)
{
	t_2dfvec	uv;

	uv.x = atan2(n.x, n.z) / (2 * M_PI) + 0.5;
	uv.y = n.y * 0.5 + 0.5;
	return (uv);
}

t_2dfvec	uv_triangle(t_solid o, t_ray_prop props)
{
	double			det;
	t_3dfvec		side;
	t_3dfvec		p;
	t_3dfvec		t;
	t_2dfvec		bar;

	side.x = o.points[2][0] - o.points[0][0];
	side.y = o.points[2][1] - o.points[0][1];
	side.z = o.points[2][2] - o.points[0][2];
	p = vecprod_3dfvec(props.dir, side);
	det = dotprod_3dfvec(o.sides[0], p);
	t = set_3dfvec(o.points[0][0], o.points[0][1], o.points[0][2]);
	bar.x = fabs(dotprod_3dfvec(t, p) / det);
	p = vecprod_3dfvec(t, o.sides[0]);
	bar.y = fabs(dotprod_3dfvec(props.dir, p) / det);
	return (bar);
}

t_2dfvec	uv_quad(t_solid o, t_ray_prop props)
{
	double			det;
	t_3dfvec		side;
	t_3dfvec		p;
	t_3dfvec		t;
	t_2dfvec		bar;

	side.x = o.points[3][0] - o.points[0][0];
	side.y = o.points[3][1] - o.points[0][1];
	side.z = o.points[3][2] - o.points[0][2];
	p = vecprod_3dfvec(props.dir, side);
	det = dotprod_3dfvec(o.sides[0], p);
	t = set_3dfvec(o.points[0][0], o.points[0][1], o.points[0][2]);
	bar.x = fabs(dotprod_3dfvec(t, p) / det);
	p = vecprod_3dfvec(t, o.sides[0]);
	bar.y = fabs(dotprod_3dfvec(props.dir, p) / det);
	return (bar);
}

static double	get_u_cylinder(t_ray_prop props, t_3dfvec direction)
{
	t_3dfvec	y;
	t_3dfvec	rod[3];
	double		alpha;
	t_3dfvec	axis;

	y = set_3dfvec(0, 1, 0);
	axis = normalize_ray(vecprod_3dfvec(direction, y));
	alpha = acos(dotprod_3dfvec(direction, y));
	rod[0] = scalprod_3dfvec(props.normal, cos(alpha));
	rod[1] = scalprod_3dfvec(vecprod_3dfvec(axis,
				props.normal), sin(alpha));
	rod[2] = scalprod_3dfvec(axis,
			dotprod_3dfvec(axis, props.normal) * (1 - cos(alpha)));
	y = vecadd_3dfvec(vecadd_3dfvec(rod[0], rod[1]), rod[2]);
	return (atan2(y.x, y.z) / (2 * M_PI) + 0.5);
}

t_2dfvec	uv_cylinder(t_solid o, t_ray_prop props)
{
	t_2dfvec	uv;
	t_3dfvec	points[2];
	t_3dfvec	direction;
	t_3dfvec	inter;
	double		alpha;

	points[0] = set_3dfvec(o.points[0][0], o.points[0][1], o.points[0][2]);
	points[1] = set_3dfvec(o.points[1][0], o.points[1][1], o.points[1][2]);
	direction = normalize_ray(vecmin_3dfvec(points[1], points[0]));
	alpha = dotprod_3dfvec(direction, vecmin_3dfvec(props.pos, points[0]));
	alpha = alpha / dotprod_3dfvec(direction, direction);
	inter = vecadd_3dfvec(points[0], scalprod_3dfvec(direction, alpha));
	uv.y = length_3dfvec(vecmin_3dfvec(inter, points[0]))
		/ length_3dfvec(direction);
	if (uv.y > 1)
		uv.y -= 1;
	uv.x = get_u_cylinder(props, direction);
	return (uv);
}
