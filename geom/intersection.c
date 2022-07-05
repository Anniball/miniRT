/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:45:18 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/19 15:11:29 by ldelmas          ###   ########.fr       */
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

t_ray_prop	do_intersect(t_ray_prop props, t_3dfvec origin, t_solid obj)
{
	if (obj.type == 's')
		props = intersect_sphere(props, origin, obj);
	else if (obj.type == 't')
		props = intersect_tri(props, origin, obj);
	else if (obj.type == 'p')
		props = intersect_plane(props, origin, obj);
	else if (obj.type == 'q')
		props = intersect_quad(props, origin, obj);
	else if (obj.type == 'c')
		props = intersect_cylinder(props, origin, obj);
	else
		props.dist = -1;
	if (props.dist > 0 && obj.mat->type == 's')
		props.m_normal = sine_normal(props, props.normal);
	else if (props.dist > 0 && obj.mat->normal.img)
		props.m_normal = normal_map(props);
	else
		props.m_normal = props.normal;
	if (props.dist > 0 && obj.mat->bump.img)
		props.m_normal = bump_map(props);
	return (props);
}

int	check_intersection(t_ray_prop props, t_solid *objs,
									t_light *lights, int background)
{
	double		max;
	t_ray_prop	save_props;
	t_solid		*tmp;

	max = -1;
	tmp = objs;
	save_props = props;
	while (objs)
	{
		props = do_intersect(props, props.ori, *objs);
		if ((props.dist < max && props.dist >= 0)
			|| (max < 0 && props.dist >= 0))
		{
			save_props = props;
			max = props.dist;
		}
		objs = objs->next;
	}
	if (max >= 0)
		return (check_shadow(save_props, tmp, lights));
	return (background);
}
