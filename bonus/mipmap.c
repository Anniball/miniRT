/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mipmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:53:11 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 15:01:29 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include "../includes/read.h"
#include "../includes/main.h"
#include "../includes/bonus.h"
#include <stdio.h>

static t_2dfvec	get_uv_by_type(t_ray_prop props, t_2dvec transfer)
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
	uv = set_2dfvec((uv.x * WIDTH) + transfer.x, (uv.y * HEIGHT) + transfer.y);
	if (uv.x >= WIDTH || uv.x < 0)
		uv.x = 0;
	if (uv.y >= HEIGHT || uv.y < 0)
		uv.y = 0;
	return (uv);
}

int	mipmap_txt(t_ray_prop props, t_data *txtr, t_2dvec transfer)
{
	double		v[4];
	int			colors[4];
	int			sum[3];
	t_2dfvec	uv;

	uv = get_uv_by_type(props, transfer);
	v[0] = ceil(uv.x) - uv.x;
	v[1] = uv.x - floor(uv.x);
	v[2] = ceil(uv.y) - uv.y;
	v[3] = uv.y - floor(uv.y);
	colors[0] = get_lightbyf(transfer_txt(props, txtr, set_2dvec(0, 0)), v[0]);
	colors[1] = get_lightbyf(transfer_txt(props, txtr, set_2dvec(1, 0)), v[1]);
	colors[2] = get_lightbyf(transfer_txt(props, txtr, set_2dvec(0, 1)), v[0]);
	colors[3] = get_lightbyf(transfer_txt(props, txtr, set_2dvec(1, 1)), v[1]);
	sum[0] = add_color(colors[0], colors[1]);
	sum[1] = add_color(colors[2], colors[3]);
	sum[2] = add_color(get_lightbyf(sum[0], v[2]), get_lightbyf(sum[1], v[3]));
	return (sum[2]);
}
