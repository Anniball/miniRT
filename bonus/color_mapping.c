/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:29:33 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 11:35:13 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "../includes/calc.h"
#include "../includes/mlx_utils.h"
#include "../includes/geom.h"
#include "../includes/bonus.h"

int	rainbow(t_3dfvec n)
{
	unsigned char	rgb[3];

	rgb[0] = (unsigned char)((unsigned int)(fabs(n.x) * 255.0));
	rgb[1] = (unsigned char)((unsigned int)(fabs(n.y) * 255.0));
	rgb[2] = (unsigned char)((unsigned int)(fabs(n.z) * 255.0));
	return (create_argb(0, rgb[0], rgb[1], rgb[2]));
}

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

int	checker(t_ray_prop props)
{
	int			ret;
	t_2dfvec	uv;

	uv = get_uv_by_type(props);
	ret = 0;
	uv.x *= 16;
	uv.y *= 16;
	if ((unsigned int)(uv.x) % 2 == 0)
		ret = 0x00FFFFFF;
	if (((unsigned int)(uv.y)) % 2 == 0)
	{
		if (!ret)
			ret = 0x00FFFFFF;
		else
			ret = 0;
	}
	return (ret);
}
