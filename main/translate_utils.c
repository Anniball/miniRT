/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:13:55 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/21 12:14:18 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "../includes/geom.h"
#include "../includes/read.h"
#include "../includes/main.h"
#include "../includes/bonus.h"

t_3dfvec	set_translation(t_3dfvec axis, double angle, t_3dfvec dir)
{
	t_3dfvec	rod[3];

	dir = normalize_ray(dir);
	rod[0] = scalprod_3dfvec(dir, cos(angle));
	rod[1] = scalprod_3dfvec(vecprod_3dfvec(axis,
				dir), sin(angle));
	rod[2] = scalprod_3dfvec(axis,
			dotprod_3dfvec(axis, dir) * (1 - cos(angle)));
	dir = vecadd_3dfvec(vecadd_3dfvec(rod[0], rod[1]), rod[2]);
	dir = normalize_ray(dir);
	return (dir);
}

int	get_pixel_color(t_2dvec screen, t_param *par, t_opti o, int col)
{
	t_ray_prop	props;
	t_3dfvec	unit[2];

	props.dir.x = ((2 * ((o.s.y) / screen.x)) - 1) * o.ratio * o.trig_fov;
	props.dir.y = (1 - (2 * ((o.s.x) / screen.y))) * o.trig_fov;
	unit[0] = scalprod_3dfvec(o.x, props.dir.x);
	unit[1] = scalprod_3dfvec(o.y, props.dir.y);
	props.dir = vecadd_3dfvec(vecadd_3dfvec(unit[0], unit[1]), o.z);
	props.dir = normalize_ray(props.dir);
	props.ori = *par->cams->position;
	return (check_intersection(props, par->objs, par->lights, col));
}

t_opti	set_local_cam(t_opti o, t_camera *cam)
{
	t_3dfvec	front;
	double		angle;
	t_3dfvec	axis;

	front = set_3dfvec(0, 0, -1);
	angle = acos(dotprod_3dfvec(front, *cam->orientation));
	axis = normalize_ray(vecprod_3dfvec(front, *cam->orientation));
	o.z = set_translation(axis, angle, front);
	o.x = set_translation(axis, angle, set_3dfvec(1, 0, 0));
	if (dotprod_3dfvec(o.x, set_3dfvec(1, 0, 0)) < 0
		&& dotprod_3dfvec(o.z, front) >= 0)
		o.x = scalprod_3dfvec(o.x, -1);
	o.y = vecprod_3dfvec(o.x, o.z);
	if (dotprod_3dfvec(o.y, set_3dfvec(0, 1, 0)) < 0)
	{
		o.y = scalprod_3dfvec(o.y, -1);
		o.x = scalprod_3dfvec(o.x, -1);
	}
	return (o);
}
