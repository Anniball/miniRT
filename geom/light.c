/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:55:18 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:17:33 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static int	front_light(t_ray_prop props, int tcol)
{
	t_3dfvec	tmp_normal;
	int			pcolor;

	tmp_normal = normalize_ray(props.normal);
	props.ratio = dotprod_3dfvec(tmp_normal, props.dir);
	if (props.ratio < 0)
		props.ratio = fabs(props.ratio);
	pcolor = get_lightbyf(tcol, props.ratio);
	return (pcolor);
}

static int	dir_light(t_ray_prop props, t_light light, int tcol)
{
	int			albedo;
	t_3dfvec	tmp_normal;
	double		factor;

	if (dotprod_3dfvec(props.normal, props.dir) < 0)
		tmp_normal = scalprod_3dfvec(props.m_normal, -1.0);
	else
		tmp_normal = props.m_normal;
	tmp_normal = normalize_ray(tmp_normal);
	factor = dotprod_3dfvec(tmp_normal, light.dir);
	if (factor < 0)
		factor = 0;
	factor = factor * (light.intensity / M_PI);
	albedo = get_albedo(tcol, light.color);
	albedo = get_lightbyf(albedo, factor);
	if (props.inters.mat->ks)
		albedo = check_specular(props, light, tmp_normal, albedo);
	return (albedo);
}

static int	point_light(t_ray_prop props, t_light light, int tcol)
{
	int			albedo;
	double		factor;
	double		angle_fctr;
	t_3dfvec	tmp_normal;

	light.dir = vecmin_3dfvec(props.pos, light.pos);
	if (dotprod_3dfvec(props.normal, props.dir) < 0)
		tmp_normal = scalprod_3dfvec(props.m_normal, -1.0);
	else
		tmp_normal = props.m_normal;
	tmp_normal = normalize_ray(tmp_normal);
	angle_fctr = dotprod_3dfvec(tmp_normal, normalize_ray(light.dir));
	if (angle_fctr < 0)
		angle_fctr = 0;
	factor = length_3dfvec(light.dir);
	factor = angle_fctr * (light.intensity / (4 * M_PI * (factor * factor)));
	albedo = get_albedo(tcol, light.color);
	albedo = get_lightbyf(albedo, factor);
	if (props.inters.mat->ks)
		albedo = check_specular(props, light, tmp_normal, albedo);
	return (albedo);
}

int	get_lights(t_ray_prop props, t_light *lights, int tcol)
{
	int	pcolor;

	pcolor = 0;
	if (lights->type == 'f')
		pcolor = front_light(props, tcol);
	else if (lights->type == 'd')
		pcolor = dir_light(props, *lights, tcol);
	else if (lights->type == 'p')
		pcolor = point_light(props, *lights, tcol);
	else if (lights->type == 'a')
	{
		pcolor = get_albedo(tcol, lights->color);
		pcolor = get_lightbyf(pcolor, lights->intensity);
	}
	lights = lights->next;
	return (pcolor);
}
