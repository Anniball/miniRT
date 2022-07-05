/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_trans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:22:39 by ldelmas           #+#    #+#             */
/*   Updated: 2021/04/13 11:49:33 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/calc.h"
#include "../includes/geom.h"
#include <stdlib.h>

double	**set_trans(t_3dfvec pos, t_3dfvec rot, t_3dfvec scale)
{
	double	**param[4];
	double	*mpos;
	t_2dvec	size;

	size = set_2dvec(3, 3);
	param[1] = set_rot(rot.x, rot.y, rot.z);
	param[2] = set_scale(scale);
	mpos = set_3dfarray(pos.x, pos.y, pos.z);
	param[3] = matrix_product(size, size, param[2], param[1]);
	if (!param[3])
		return ((void *)0);
	free(*(param[1]));
	free(param[1]);
	free(*(param[2]));
	free(param[2]);
	param[0] = set_transmatrix(param[3][0], param[3][1], param[3][2], mpos);
	if (!param[0])
		return ((void *)0);
	free(mpos);
	free(*param[3]);
	free(param[3]);
	return (param[0]);
}

double	**set_obj_to_cam(t_3dfvec pos, t_3dfvec rot,
						t_3dfvec scale, double **cam)
{
	double	**trans;
	double	**obj;
	t_2dvec	size;

	size = set_2dvec(4, 4);
	obj = set_trans(pos, rot, scale);
	trans = matrix_product(size, size, obj, cam);
	free(*obj);
	free(obj);
	return (trans);
}
