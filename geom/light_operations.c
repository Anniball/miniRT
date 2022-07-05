/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:38:18 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:18:40 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int	get_lightbyf(int color, double val)
{
	unsigned char		a;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;

	a = get_a(&color);
	r = (unsigned int)(val * (double)((unsigned char)get_r(&color)));
	g = (unsigned int)(val * (double)((unsigned char)get_g(&color)));
	b = (unsigned int)(val * (double)((unsigned char)get_b(&color)));
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (create_argb(a, (char)r, (char)g, (char)b));
}

static double	get_albedo_rgb(char (*f)(int*), int num, int den)
{
	double			af;
	unsigned char	a;

	a = (*f)(&den);
	af = (a * (double)((unsigned char)(*f)(&num))) / 255;
	if (a)
		a = (unsigned char)(af);
	return (a);
}

int	get_albedo(int num, int den)
{
	unsigned char		a[3];

	a[0] = get_albedo_rgb(&get_r, num, den);
	a[1] = get_albedo_rgb(&get_g, num, den);
	a[2] = get_albedo_rgb(&get_b, num, den);
	return (create_argb(get_a(&num), a[0], a[1], a[2]));
}

int	check_specular(t_ray_prop props, t_light light,
									t_3dfvec normal, int diffuse)
{
	double		spec;
	t_3dfvec	opp;
	t_3dfvec	bounce;
	int			color;

	opp = set_3dfvec(-props.dir.x, -props.dir.y, -props.dir.z);
	spec = dotprod_3dfvec(normal, light.dir);
	bounce = scalprod_3dfvec(normal, 2 * spec);
	bounce = vecmin_3dfvec(bounce, light.dir);
	bounce = normalize_ray(bounce);
	spec = dotprod_3dfvec(opp, bounce);
	spec = pow_double(spec, props.inters.mat->n);
	diffuse = get_lightbyf(diffuse, 1 - props.inters.mat->ks);
	color = get_lightbyf(light.color, spec * props.inters.mat->ks);
	color = add_color(color, diffuse);
	return (color);
}
