/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:45:12 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 15:01:27 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include "../includes/bonus.h"

static t_2dfvec	get_uv_by_type(t_ray_prop props)
{
	t_2dfvec	uv;

	uv = set_2dfvec(0, 0);
	if (props.inters.type == 's')
		uv = uv_sphere(props.normal);
	else if (props.inters.type == 't')
		uv = uv_triangle(props.inters, props);
	else if (props.inters.type == 'q')
		uv = uv_quad(props.inters, props);
	else if (props.inters.type == 'c')
		uv = uv_cylinder(props.inters, props);
	return (uv);
}

t_3dfvec	sine_normal(t_ray_prop props, t_3dfvec n)
{
	t_3dfvec	normal;
	t_3dfvec	axis;
	double		angle;
	t_3dfvec	rod[3];
	t_2dfvec	uv;

	uv = get_uv_by_type(props);
	normal = set_3dfvec(0, 1, 0);
	n = normalize_ray(n);
	axis = normalize_ray(vecprod_3dfvec(normal, n));
	angle = acos(dotprod_3dfvec(normal, n));
	normal.x += (sin(uv.y * 50) * 1);
	normal = normalize_ray(normal);
	rod[0] = scalprod_3dfvec(normal, cos(angle));
	rod[1] = scalprod_3dfvec(vecprod_3dfvec(axis, normal), sin(angle));
	rod[2] = scalprod_3dfvec(axis,
			dotprod_3dfvec(axis, normal) * (1 - cos(angle)));
	normal = vecadd_3dfvec(vecadd_3dfvec(rod[0], rod[1]), rod[2]);
	return (normal);
}

t_3dfvec	normal_map(t_ray_prop props)
{
	t_3dfvec	axis;
	double		angle;
	t_3dfvec	rod[3];
	int			color;
	t_2dfvec	uv;

	uv = get_uv_by_type(props);
	props.m_normal = set_3dfvec(0, 0, 1);
	props.normal = normalize_ray(props.normal);
	axis = normalize_ray(vecprod_3dfvec(props.m_normal, props.normal));
	angle = acos(dotprod_3dfvec(props.m_normal, props.normal));
	color = mipmap_txt(props, &(props.inters.mat->normal), set_2dvec(0, 0));
	props.m_normal.x = (int)((unsigned char)(get_r(&color)) - 128);
	props.m_normal.y = (int)((unsigned char)(get_g(&color)) - 128);
	props.m_normal.z = (int)((unsigned char)(get_b(&color)) - 128);
	props.m_normal = normalize_ray(props.m_normal);
	rod[0] = scalprod_3dfvec(props.m_normal, cos(angle));
	rod[1] = scalprod_3dfvec(vecprod_3dfvec(axis, props.m_normal), sin(angle));
	rod[2] = scalprod_3dfvec(axis,
			dotprod_3dfvec(axis, props.m_normal) * (1 - cos(angle)));
	props.m_normal = vecadd_3dfvec(vecadd_3dfvec(rod[0], rod[1]), rod[2]);
	props.m_normal = normalize_ray(props.m_normal);
	return (props.m_normal);
}

t_3dfvec	get_bump(t_ray_prop props)
{
	int			color[4];
	t_3dfvec	bump;

	color[0] = transfer_txt(props, &(props.inters.mat->bump), set_2dvec(1, 0));
	color[1] = transfer_txt(props, &(props.inters.mat->bump), set_2dvec(-1, 0));
	color[2] = transfer_txt(props, &(props.inters.mat->bump), set_2dvec(0, 1));
	color[3] = transfer_txt(props, &(props.inters.mat->bump), set_2dvec(0, -1));
	bump.x = (double)((int)((unsigned char)(get_r(color)))
			- (unsigned char)(get_r(color + 1))) / 128.0;
	bump.y = (double)((int)((unsigned char)(get_r(color + 2)))
			- (unsigned char)(get_r(color + 3))) / 128.0;
	bump.z = 1;
	return (bump);
}

t_3dfvec	bump_map(t_ray_prop props)
{
	t_3dfvec	bump;
	t_2dfvec	uv;
	t_3dfvec	axis;
	double		angle;
	t_3dfvec	rod[3];

	uv = get_uv_by_type(props);
	bump = get_bump(props);
	normalize_ray(bump);
	axis = normalize_ray(vecprod_3dfvec(set_3dfvec(0, 0, 1), props.m_normal));
	angle = acos(dotprod_3dfvec(set_3dfvec(0, 0, 1),
				normalize_ray(props.m_normal)));
	rod[0] = scalprod_3dfvec(bump, cos(angle));
	rod[1] = scalprod_3dfvec(vecprod_3dfvec(axis, bump), sin(angle));
	rod[2] = scalprod_3dfvec(axis,
			dotprod_3dfvec(axis, bump) * (1 - cos(angle)));
	props.m_normal = vecadd_3dfvec(vecadd_3dfvec(rod[0], rod[1]), rod[2]);
	props.m_normal = normalize_ray(props.m_normal);
	return (props.m_normal);
}
