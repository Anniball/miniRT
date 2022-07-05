/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:06:19 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/12 11:16:05 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "../includes/geom.h"
#include "../includes/read.h"
#include "../includes/mlx_utils.h"
#include "../includes/main.h"
#include "../includes/bonus.h"

static int	col_average(int *colors, int size)
{
	unsigned int	rgb[3];
	unsigned char	col[3];
	int				i;

	i = -1;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	while (++i < size)
	{
		rgb[0] += (unsigned int)((unsigned char)(get_r(colors + i)));
		rgb[1] += (unsigned int)((unsigned char)(get_g(colors + i)));
		rgb[2] += (unsigned int)((unsigned char)(get_b(colors + i)));
	}
	rgb[0] /= size;
	rgb[1] /= size;
	rgb[2] /= size;
	col[0] = (unsigned char)(rgb[0]);
	col[1] = (unsigned char)(rgb[1]);
	col[2] = (unsigned char)(rgb[2]);
	free(colors);
	return (create_argb(0, col[0], col[1], col[2]));
}

int	set_aa(t_2dvec screen, t_param *par, t_opti o)
{
	t_2dvec		i;
	int			*colors;
	t_2dfvec	s;
	double		corrector;

	colors = malloc(sizeof(colors) * par->aa * par->aa);
	if (!colors)
		return (-1);
	corrector = (double)par->aa / (par->aa - 1);
	s = set_2dfvec(o.s.x - 0.5, o.s.y - 0.5);
	i.x = -1;
	while (++(i.x) < par->aa)
	{
		o.s.x = s.x + (((double)i.x / par->aa) * corrector);
		i.y = -1;
		while (++(i.y) < par-> aa)
		{
			o.s.y = s.y + (((double)i.y / par->aa) * corrector);
			colors[i.y * (i.x + 1)] = get_pixel_color(screen, par, o,
					get_background_pixel(set_2dvec((int)s.x,
							(int)s.y), screen, par->skybox));
		}
	}
	return (col_average(colors, par->aa));
}
