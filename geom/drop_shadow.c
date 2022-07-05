/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 11:40:32 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/19 15:12:43 by ldelmas          ###   ########.fr       */
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

static t_3dfvec	define_bias(t_3dfvec dir, t_3dfvec normal, t_3dfvec pos)
{
	double		bias;

	bias = 0.0001;
	if (dotprod_3dfvec(dir, normal) < 0)
		bias = -bias;
	pos.x = pos.x + (normal.x * bias);
	pos.y = pos.y + (normal.y * bias);
	pos.z = pos.z + (normal.z * bias);
	return (pos);
}

static void	add_light(int *tot, t_solid *obj, t_ray_prop props, t_light *l)
{
	int			pcolor;
	int			tcolor;

	pcolor = 0;
	if (props.inters.mat->type == 'n')
		pcolor = rainbow(props.m_normal);
	else if (!obj)
	{
		if (props.inters.mat->type == 'c')
			tcolor = checker(props);
		else if (props.inters.mat->type == 't' && props.inters.mat->texture.img)
			tcolor = mipmap_txt(props, &(props.inters.mat->texture),
					set_2dvec(0, 0));
		else
			tcolor = props.inters.mat->color;
		pcolor = get_lights(props, l, tcolor);
	}
	*tot = add_color(*tot, pcolor);
}

static t_solid	*check_objs(t_light *lights, t_ray_prop t_props,
								t_ray_prop props, t_solid *objs)
{
	double	len;

	if (lights->type == 'p')
	{
		len = length_3dfvec(t_props.dir);
		t_props.dir = normalize_ray(t_props.dir);
	}
	if (lights->type == 'a')
		objs = (void *)0;
	while (objs)
	{
		t_props = do_intersect(t_props,
				define_bias(t_props.dir, props.normal, props.pos), *objs);
		if (t_props.dist >= 0 && (lights->type != 'p'
				|| (lights->type == 'p' && t_props.dist < len)))
			break ;
		objs = objs->next;
	}
	return (objs);
}

int	check_shadow(t_ray_prop props, t_solid *objs, t_light *lights)
{
	t_ray_prop	t_props;
	t_solid		*tmp;
	int			tot;

	tot = 0;
	tmp = objs;
	while (lights)
	{
		if (lights->type == 'f')
			t_props.dir = scalprod_3dfvec(props.dir, -1.0);
		else if (lights->type == 'd')
			t_props.dir = scalprod_3dfvec(lights->dir, -1.0);
		else if (lights->type == 'p')
			t_props.dir = vecmin_3dfvec(lights->pos, props.pos);
		objs = tmp;
		objs = check_objs(lights, t_props, props, objs);
		add_light(&tot, objs, props, lights);
		lights = lights->next;
	}
	return (tot);
}
