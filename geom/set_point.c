/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 11:35:10 by ldelmas           #+#    #+#             */
/*   Updated: 2021/03/18 10:24:43 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include "../includes/mlx_utils.h"
#include <stdlib.h>
#include <stdio.h>

double	*set_point_by_ref(double posx, double posy, double posz, double **ref)
{
	double	*point;
	double	**point_r;
	t_2dvec	point_size;
	t_2dvec	trans_size;

	point_size = set_2dvec(1, 4);
	trans_size = set_2dvec(4, 4);
	point = set_4dfarray(posx, posy, posz, 1);
	point_r = matrix_product(point_size, trans_size, &point, ref);
	free(point);
	point = *point_r;
	free(point_r);
	return (point);
}
