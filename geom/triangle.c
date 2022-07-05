/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:44:48 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:57:28 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

static t_3dfvec	get_side(double **points)
{
	t_3dfvec	side;

	side.x = points[2][0] - points[0][0];
	side.y = points[2][1] - points[0][1];
	side.z = points[2][2] - points[0][2];
	return (side);
}

t_ray_prop	intersect_tri(t_ray_prop props, t_3dfvec o, t_solid obj)
{
	double			det;
	t_3dfvec		side;
	t_3dfvec		p;
	t_3dfvec		t;
	t_2dfvec		bar;

	props.dist = -1;
	side = get_side(obj.points);
	p = vecprod_3dfvec(props.dir, side);
	det = dotprod_3dfvec(obj.sides[0], p);
	t = set_3dfvec(o.x - obj.points[0][0], o.y - obj.points[0][1],
			o.z - obj.points[0][2]);
	bar.x = dotprod_3dfvec(t, p) / det;
	if (bar.x < 0 || bar.x > 1)
		return (props);
	p = vecprod_3dfvec(t, obj.sides[0]);
	bar.y = dotprod_3dfvec(props.dir, p) / det;
	if (bar.y < 0 || bar.x + bar.y > 1)
		return (props);
	props.dist = dotprod_3dfvec(side, p) / det;
	props.normal = obj.normal;
	props.inters = obj;
	props.pos = vecadd_3dfvec(o, scalprod_3dfvec(props.dir, props.dist));
	return (props);
}

static double	**get_tri_points(double **trans, t_3dfvec *pts)
{
	double	**points;

	points = malloc(sizeof(*points) * 4);
	if (!points)
		return ((void *)0);
	points[0] = set_point_by_ref(pts[0].x, pts[0].y, pts[0].z, trans);
	points[1] = set_point_by_ref(pts[1].x, pts[1].y, pts[1].z, trans);
	points[2] = set_point_by_ref(pts[2].x, pts[2].y, pts[2].z, trans);
	points[3] = (void *)0;
	return (points);
}

static t_3dfvec	*get_tri_sides(t_solid triangle)
{
	t_3dfvec	*side;

	side = malloc(sizeof(*side) * 3);
	if (!side)
		return ((void *)0);
	side[0].x = triangle.points[1][0] - triangle.points[0][0];
	side[0].y = triangle.points[1][1] - triangle.points[0][1];
	side[0].z = triangle.points[1][2] - triangle.points[0][2];
	side[1].x = triangle.points[2][0] - triangle.points[1][0];
	side[1].y = triangle.points[2][1] - triangle.points[1][1];
	side[1].z = triangle.points[2][2] - triangle.points[1][2];
	side[2].x = triangle.points[0][0] - triangle.points[2][0];
	side[2].y = triangle.points[0][1] - triangle.points[2][1];
	side[2].z = triangle.points[0][2] - triangle.points[2][2];
	return (side);
}

t_solid	*set_triangle(double **trans, t_3dfvec *points,
								t_solid *next, t_material *mat)
{
	t_solid		*triangle;

	triangle = malloc(sizeof(*triangle));
	triangle->points = get_tri_points(trans, points);
	triangle->sides = get_tri_sides(*triangle);
	if (!triangle || !triangle->points || !triangle->sides)
	{
		free(triangle);
		free(triangle->points);
		free(triangle->sides);
		return ((void *)0);
	}
	triangle->type = 't';
	triangle->trans = trans;
	triangle->normal.x = triangle->points[2][0] - triangle->points[0][0];
	triangle->normal.y = triangle->points[2][1] - triangle->points[0][1];
	triangle->normal.z = triangle->points[2][2] - triangle->points[0][2];
	triangle->normal = vecprod_3dfvec(triangle->sides[0], triangle->normal);
	triangle->next = next;
	triangle->mat = mat;
	return (triangle);
}
