/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:26:27 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:29:41 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

t_solid	*set_cylinder(double **trans, t_solid *next,
									t_material *mat, t_3dfvec scale)
{
	t_solid	*cylinder;

	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
		return ((void *)0);
	cylinder->type = 'c';
	cylinder->scale = scale;
	cylinder->trans = trans;
	cylinder->points = malloc(sizeof(*(cylinder->points)) * 3);
	if (!cylinder->points)
		return ((void *)0);
	cylinder->points[0] = set_point_by_ref(0, 1, 0, trans);
	cylinder->points[1] = set_point_by_ref(0, -1, 0, trans);
	cylinder->points[2] = (void *)0;
	cylinder->sides = (void *)0;
	cylinder->next = next;
	cylinder->mat = mat;
	return (cylinder);
}
