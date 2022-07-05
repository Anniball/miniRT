/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:45:55 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:33:35 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <stdlib.h>
#include <stdio.h>

static t_3dfvec	get_side(double **points)
{
	t_3dfvec	side;

	side.x = points[3][0] - points[0][0];
	side.y = points[3][1] - points[0][1];
	side.z = points[3][2] - points[0][2];
	return (side);
}

t_ray_prop	intersect_quad(t_ray_prop props, t_3dfvec o, t_solid obj)
{
	t_2dfvec	bary_t;
	double		det;
	t_3dfvec	side;
	t_3dfvec	p;
	t_3dfvec	t;

	props.dist = -1;
	side = get_side(obj.points);
	p = vecprod_3dfvec(props.dir, side);
	det = dotprod_3dfvec(obj.sides[0], p);
	t = set_3dfvec(o.x - obj.points[0][0], o.y - obj.points[0][1],
			o.z - obj.points[0][2]);
	bary_t.x = dotprod_3dfvec(t, p) / det;
	if (bary_t.x < 0 || bary_t.x > 1)
		return (props);
	p = vecprod_3dfvec(t, obj.sides[0]);
	bary_t.y = dotprod_3dfvec(props.dir, p) / det;
	if (bary_t.y < 0 || bary_t.y > 1)
		return (props);
	props.dist = dotprod_3dfvec(side, p) / det;
	props.normal = obj.normal;
	props.inters = obj;
	props.pos = vecadd_3dfvec(o, scalprod_3dfvec(props.dir, props.dist));
	return (props);
}

static double	**get_quad_points(double **trans)
{
	double	**points;

	points = malloc(sizeof(*points) * 5);
	if (!points)
		return ((void *)0);
	points[0] = set_point_by_ref(1, 1, 0, trans);
	points[1] = set_point_by_ref(-1, 1, 0, trans);
	points[2] = set_point_by_ref(-1, -1, 0, trans);
	points[3] = set_point_by_ref(1, -1, 0, trans);
	points[4] = (void *)0;
	return (points);
}

static t_3dfvec	*get_quad_sides(t_solid quad)
{
	t_3dfvec	*side;

	side = malloc(sizeof(*side) * 4);
	if (!side)
		return ((void *)0);
	side[0].x = quad.points[1][0] - quad.points[0][0];
	side[0].y = quad.points[1][1] - quad.points[0][1];
	side[0].z = quad.points[1][2] - quad.points[0][2];
	side[1].x = quad.points[2][0] - quad.points[1][0];
	side[1].y = quad.points[2][1] - quad.points[1][1];
	side[1].z = quad.points[2][2] - quad.points[1][2];
	side[2].x = quad.points[3][0] - quad.points[2][0];
	side[2].y = quad.points[3][1] - quad.points[2][1];
	side[2].z = quad.points[3][2] - quad.points[2][2];
	side[3].x = quad.points[0][0] - quad.points[3][0];
	side[3].y = quad.points[0][1] - quad.points[3][1];
	side[3].z = quad.points[0][2] - quad.points[3][2];
	return (side);
}

t_solid	*set_quad(double **trans, t_solid *next, t_material *mat)
{
	t_solid		*quad;

	quad = malloc(sizeof(*quad));
	quad->points = get_quad_points(trans);
	quad->sides = get_quad_sides(*quad);
	if (!quad || !quad->points || !quad->sides)
	{
		free(quad);
		free(quad->points);
		free(quad->sides);
		return ((void *)0);
	}
	quad->type = 'q';
	quad->trans = trans;
	quad->normal.x = quad->points[3][0] - quad->points[0][0];
	quad->normal.y = quad->points[3][1] - quad->points[0][1];
	quad->normal.z = quad->points[3][2] - quad->points[0][2];
	quad->normal = vecprod_3dfvec(quad->sides[0], quad->normal);
	quad->next = next;
	quad->mat = mat;
	return (quad);
}
