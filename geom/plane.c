/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:49:34 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:24:11 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <stdlib.h>
#include <stdio.h>

t_ray_prop	intersect_plane(t_ray_prop props, t_3dfvec o, t_solid obj)
{
	t_3dfvec		point;
	double			den;

	den = dotprod_3dfvec(obj.normal, props.dir);
	point = set_3dfvec(obj.points[0][0], obj.points[0][1], obj.points[0][2]);
	point = set_3dfvec(point.x - o.x, point.y - o.y, point.z - o.z);
	props.dist = dotprod_3dfvec(point, obj.normal) / den;
	if (props.dist >= 0)
	{
		props.normal = obj.normal;
		props.inters = obj;
		props.pos.x = o.x + (props.dist * props.dir.x);
		props.pos.y = o.y + (props.dist * props.dir.y);
		props.pos.z = o.z + (props.dist * props.dir.z);
	}
	return (props);
}

static double	**get_plane_points(double **trans)
{
	double	**points;

	points = malloc(sizeof(*points) * 4);
	if (!points)
		return ((void *)0);
	points[0] = set_point_by_ref(0, 1, 0, trans);
	points[1] = set_point_by_ref(-1, -1, 0, trans);
	points[2] = set_point_by_ref(1, -1, 0, trans);
	points[3] = (void *)0;
	return (points);
}

t_solid	*set_plane(double **trans, t_solid *next, t_material *mat)
{
	t_solid		*plane;
	t_3dfvec	side;

	plane = malloc(sizeof(*plane));
	if (!plane)
		return ((void *)0);
	plane->points = get_plane_points(trans);
	if (!plane->points)
	{
		free(plane);
		return ((void *)0);
	}
	plane->type = 'p';
	plane->trans = trans;
	plane->normal.x = plane->points[2][0] - plane->points[0][0];
	plane->normal.y = plane->points[2][1] - plane->points[0][1];
	plane->normal.z = plane->points[2][2] - plane->points[0][2];
	side.x = plane->points[1][0] - plane->points[0][0];
	side.y = plane->points[1][1] - plane->points[0][1];
	side.z = plane->points[1][2] - plane->points[0][2];
	plane->normal = vecprod_3dfvec(side, plane->normal);
	plane->sides = (void *)0;
	plane->next = next;
	plane->mat = mat;
	return (plane);
}
